/*
 * hill.c
 *
 * Hill Cipher (2x2)
 * -----------------
 * The Hill cipher is a block cipher based on linear algebra.
 * Instead of encrypting one letter at a time, it encrypts blocks of letters
 * using matrix multiplication modulo 26.
 *
 * Letter-to-number mapping:
 *   A -> 0, B -> 1, ..., Z -> 25
 *
 * For a 2x2 Hill cipher, we encrypt pairs of letters (a vector of length 2):
 *   P = [p0, p1]^T
 *
 * Using a 2x2 key matrix K:
 *   K = [ a  b ]
 *       [ c  d ]
 *
 * Encryption:
 *   C = K * P (mod 26)
 *
 * Decryption:
 *   P = K^-1 * C (mod 26)
 *
 * IMPORTANT CONSTRAINT:
 *   The key matrix K must be invertible modulo 26.
 *   This is true only when det(K) is relatively prime to 26:
 *      gcd(det(K), 26) == 1
 *
 * Where:
 *   det(K) = (a*d - b*c) mod 26
 *
 * Small example (from the lab):
 *   Plaintext "HELP"
 *   K = [1 8]
 *       [8 5]
 *   Output ciphertext should be "NYBH"
 *
 * Input behavior for this project:
 *   - Letters only: non-letter characters are omitted (not preserved).
 *   - All letters are converted to uppercase.
 *   - If the number of letters is odd, we pad the final block with 'X'.
 *   - On decrypt, we remove a trailing 'X' padding if present.
 */

#include "hill.h"
#include "utils.h"

 /* ---------------- Small math helpers ---------------- */

 /*
  * mod26(x)
  * --------
  * Ensures a value is always in [0..25].
  *
  * Why this exists:
  *   In C, the % operator can return a negative remainder.
  *   For modular arithmetic we always want a positive representative.
  */
static int mod26(int x)
{
    int r = x % 26;
    if (r < 0) r += 26;
    return r;
}

/*
 * gcd(a, b)
 * ---------
 * Greatest common divisor (Euclid's algorithm).
 *
 * Why we need this:
 *   For Hill cipher, the determinant must be invertible mod 26.
 *   That requires gcd(det, 26) == 1.
 */
static int gcd(int a, int b)
{
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return (a < 0) ? -a : a;
}

/*
 * mod_inverse_26(a)
 * -----------------
 * Finds a^-1 mod 26 (the modular multiplicative inverse).
 *
 * Returns:
 *   x in [0..25] such that (a*x) mod 26 == 1
 *   -1 if no inverse exists
 *
 * Notes:
 *   26 is small, so brute-force is simple and reliable.
 */
static int mod_inverse_26(int a)
{
    int a_mod = mod26(a);

    for (int x = 0; x < 26; x++) {
        if ((a_mod * x) % 26 == 1) return x;
    }
    return -1;
}

/*
 * extract_letters(in, out, max_out)
 * ---------------------------------
 * Copies letters only from input -> output, uppercases them.
 *
 * Returns:
 *   number of letters copied
 *
 * Why:
 *   Our Hill implementation is letters-only (like our Playfair).
 */
static int extract_letters(const char* in, char* out, int max_out)
{
    int n = 0;

    for (int i = 0; in[i] != '\0' && n < max_out - 1; i++) {
        if (is_alpha(in[i])) {
            out[n++] = to_upper(in[i]);
        }
    }

    out[n] = '\0';
    return n;
}

/*
 * invert_key_2x2(K, Kinv)
 * -----------------------
 * Computes the modular inverse of a 2x2 matrix K modulo 26.
 *
 * K = [a b]
 *     [c d]
 *
 * det = (a*d - b*c) mod 26
 *
 * K^-1 = det^-1 * [ d  -b ]
 *                [ -c  a ]  (mod 26)
 *
 * Returns:
 *   1 if invertible and Kinv is filled in
 *   0 if K is not invertible mod 26
 */
static int invert_key_2x2(int K[2][2], int Kinv[2][2])
{
    int a = mod26(K[0][0]);
    int b = mod26(K[0][1]);
    int c = mod26(K[1][0]);
    int d = mod26(K[1][1]);

    /* Compute determinant det(K) in modulo arithmetic */
    int det = mod26(a * d - b * c);

    /* det must be coprime with 26 to be invertible */
    if (gcd(det, 26) != 1) {
        return 0;
    }

    /* Compute det inverse */
    int det_inv = mod_inverse_26(det);
    if (det_inv == -1) {
        return 0;
    }

    /* Build adjugate matrix and multiply by det_inv (all mod 26) */
    Kinv[0][0] = mod26(det_inv * d);
    Kinv[0][1] = mod26(det_inv * (-b));
    Kinv[1][0] = mod26(det_inv * (-c));
    Kinv[1][1] = mod26(det_inv * a);

    return 1;
}

/* ---------------- Public API ---------------- */

void hill_encrypt_2x2(const char* plaintext, char* ciphertext, int K[2][2])
{
    char letters[512];
    char padded[512];

    /* Step 1: keep letters only */
    int n = extract_letters(plaintext, letters, (int)sizeof(letters));

    /* Step 2: pad with 'X' if odd length so we always have pairs */
    int p = 0;
    for (int i = 0; i < n && p < (int)sizeof(padded) - 1; i++) {
        padded[p++] = letters[i];
    }
    if (p % 2 != 0 && p < (int)sizeof(padded) - 1) {
        padded[p++] = 'X';
    }
    padded[p] = '\0';

    /* Step 3: encrypt in blocks of 2 letters */
    int out = 0;
    for (int i = 0; i < p; i += 2) {
        /* Convert letters to numeric vector P */
        int P0 = char_to_int(padded[i]);       /* 0..25 */
        int P1 = char_to_int(padded[i + 1]);   /* 0..25 */

        /* Matrix multiply C = K * P (mod 26)
           [C0] = [K00 K01] [P0]
           [C1]   [K10 K11] [P1] */
        int C0 = mod26(K[0][0] * P0 + K[0][1] * P1);
        int C1 = mod26(K[1][0] * P0 + K[1][1] * P1);

        /* Convert back to letters */
        ciphertext[out++] = int_to_char(C0);
        ciphertext[out++] = int_to_char(C1);
    }

    ciphertext[out] = '\0';
}

void hill_decrypt_2x2(const char* ciphertext, char* plaintext, int K[2][2])
{
    int Kinv[2][2];

    /* Step 1: compute inverse key matrix */
    if (!invert_key_2x2(K, Kinv)) {
        /* Safe failure behavior:
           If K has no inverse mod 26, decryption cannot be performed.
           We copy letters-only ciphertext back so the program doesn't crash
           or produce random output. */
        char letters[512];
        extract_letters(ciphertext, letters, (int)sizeof(letters));

        int i = 0;
        while (letters[i] != '\0') {
            plaintext[i] = letters[i];
            i++;
        }
        plaintext[i] = '\0';
        return;
    }

    /* Step 2: sanitize ciphertext to letters only */
    char letters[512];
    int n = extract_letters(ciphertext, letters, (int)sizeof(letters));

    /* Hill ciphertext should always have even length.
       If it's odd for some reason, we fail safely by copying. */
    if (n % 2 != 0) {
        int i = 0;
        while (letters[i] != '\0') {
            plaintext[i] = letters[i];
            i++;
        }
        plaintext[i] = '\0';
        return;
    }

    /* Step 3: decrypt in pairs using P = Kinv * C (mod 26) */
    int out = 0;
    for (int i = 0; i < n; i += 2) {
        int C0 = char_to_int(letters[i]);
        int C1 = char_to_int(letters[i + 1]);

        int P0 = mod26(Kinv[0][0] * C0 + Kinv[0][1] * C1);
        int P1 = mod26(Kinv[1][0] * C0 + Kinv[1][1] * C1);

        plaintext[out++] = int_to_char(P0);
        plaintext[out++] = int_to_char(P1);
    }
    plaintext[out] = '\0';

    /* Step 4 (optional cleanup):
       If we padded with X during encryption, remove a trailing X. */
    if (out > 0 && plaintext[out - 1] == 'X') {
        plaintext[out - 1] = '\0';
    }
}
