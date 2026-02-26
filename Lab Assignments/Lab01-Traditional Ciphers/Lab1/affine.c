/*
 * affine.c
 *
 * Affine Cipher
 * ------------
 * The Affine cipher is a substitution cipher based on a linear function over Z_26.
 *
 * Letter-to-number mapping:
 *   A -> 0, B -> 1, ..., Z -> 25
 *
 * Encryption formula:
 *   C = (aP + b) mod 26
 *
 * Decryption formula:
 *   P = a_inv * (C - b) mod 26
 *
 * Where:
 *   - P is the plaintext value (0..25)
 *   - C is the ciphertext value (0..25)
 *   - a and b are integer keys
 *   - a_inv is the modular multiplicative inverse of a (mod 26)
 *
 * Small example:
 *   Let a = 5, b = 8
 *   Plaintext letter: 'B' -> P = 1
 *   Encryption: C = (5 * 1 + 8) mod 26 = 13 -> 'N'
 *   Decryption: P = a_inv * (13 - 8) mod 26 = 1 -> 'B'
 *
 * IMPORTANT CONSTRAINT:
 *   'a' must be invertible mod 26, which only happens when gcd(a, 26) == 1.
 *   If gcd(a,26) != 1, then decryption is impossible.
 *
 * Input behavior for this project:
 *   - Alphabetic characters are encrypted/decrypted (case-insensitive; output is uppercase).
 *   - Non-alphabetic characters (spaces, punctuation, digits) are preserved unchanged.
 */

#include "affine.h"
#include "utils.h"

 /*
  * gcd(x, y)
  * ---------
  * Computes the greatest common divisor using Euclid's algorithm.
  *
  * Why we need this:
  *   The Affine cipher requires gcd(a, 26) == 1 to ensure that 'a' has a modular inverse.
  *   If 'a' has no inverse, we cannot decrypt.
  */
static int gcd(int x, int y)
{
    /* Euclid's algorithm repeatedly reduces the problem:
       gcd(x, y) = gcd(y, x % y) until y becomes 0. */
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }

    /* Ensure gcd is non-negative. */
    return (x < 0) ? -x : x;
}

/*
 * mod_inverse_26(a)
 * -----------------
 * Finds the modular inverse of 'a' modulo 26.
 *
 * Returns:
 *   - a value in [0..25] such that (a * a_inv) mod 26 == 1, if it exists
 *   - -1 if no inverse exists
 *
 * How it works:
 *   Since 26 is small, we can brute-force search for x in [0..25] and test:
 *     (a_mod * x) % 26 == 1
 */
static int mod_inverse_26(int a)
{
    /* Reduce 'a' into the equivalent value modulo 26 (and make it positive). */
    int a_mod = a % 26;
    if (a_mod < 0) a_mod += 26;

    /* Brute-force is acceptable here because modulus is tiny (26). */
    for (int x = 0; x < 26; x++) {
        if ((a_mod * x) % 26 == 1) {
            return x;
        }
    }

    /* If we didn't find x, inverse does not exist. */
    return -1;
}

/*
 * mod26(x)
 * --------
 * Ensures we always return a value in the range [0..25].
 *
 * In C, the % operator can return negative values for negative inputs,
 * so we normalize it to be non-negative.
 *
 * Example:
 *   -1 % 26 == -1 in C, but we want 25
 */
static int mod26(int x)
{
    int r = x % 26;
    if (r < 0) r += 26;
    return r;
}

/*
 * affine_encrypt(plaintext, ciphertext, a, b)
 * -------------------------------------------
 * Encrypts plaintext using the Affine cipher and stores the result in ciphertext.
 *
 * Behavior:
 *   - Letters are encrypted and written as uppercase.
 *   - Non-letters are copied as-is.
 *
 * Safety behavior:
 *   If 'a' is invalid (gcd(a,26) != 1), the function copies plaintext to ciphertext unchanged.
 *   (This prevents producing garbage output when the key is mathematically invalid.)
 */
void affine_encrypt(const char* plaintext, char* ciphertext, int a, int b)
{
    int i = 0;

    /* Validate that 'a' is invertible mod 26. If not, encryption isn't meaningful
       for our assignment's decrypt requirement, so we "fail safe" by copying. */
    if (gcd(a, 26) != 1) {
        while (plaintext[i] != '\0') {
            ciphertext[i] = plaintext[i];
            i++;
        }
        ciphertext[i] = '\0';
        return;
    }

    /* Process the input string character-by-character. */
    while (plaintext[i] != '\0') {
        char ch = plaintext[i];

        if (is_alpha(ch)) {
            /* Normalize to uppercase so A..Z mapping is consistent. */
            ch = to_upper(ch);

            /* Convert letter to number 0..25. */
            int p = char_to_int(ch);

            /* Apply Affine encryption formula: C = (aP + b) mod 26. */
            int c = mod26(a * p + b);

            /* Convert numeric result back to uppercase letter. */
            ciphertext[i] = int_to_char(c);
        }
        else {
            /* Non-letters are not encrypted for this implementation. */
            ciphertext[i] = plaintext[i];
        }

        i++;
    }

    /* Null-terminate output string. */
    ciphertext[i] = '\0';
}

/*
 * affine_decrypt(ciphertext, plaintext, a, b)
 * -------------------------------------------
 * Decrypts ciphertext using the Affine cipher and stores the result in plaintext.
 *
 * Decryption formula:
 *   P = a_inv * (C - b) mod 26
 *
 * Where:
 *   a_inv is the modular inverse of 'a' mod 26
 *
 * Safety behavior:
 *   - If gcd(a,26) != 1, we copy ciphertext to plaintext unchanged
 *   - If mod_inverse_26(a) fails, we also copy unchanged
 */
void affine_decrypt(const char* ciphertext, char* plaintext, int a, int b)
{
    int i = 0;

    /* If 'a' is not invertible, we cannot decrypt. */
    if (gcd(a, 26) != 1) {
        while (ciphertext[i] != '\0') {
            plaintext[i] = ciphertext[i];
            i++;
        }
        plaintext[i] = '\0';
        return;
    }

    /* Compute the modular inverse of 'a'. */
    int a_inv = mod_inverse_26(a);

    /* If inverse doesn't exist (shouldn't happen if gcd(a,26)==1, but we guard anyway),
       copy safely. */
    if (a_inv == -1) {
        while (ciphertext[i] != '\0') {
            plaintext[i] = ciphertext[i];
            i++;
        }
        plaintext[i] = '\0';
        return;
    }

    /* Decrypt each character. */
    while (ciphertext[i] != '\0') {
        char ch = ciphertext[i];

        if (is_alpha(ch)) {
            ch = to_upper(ch);

            /* Convert letter to number 0..25. */
            int c = char_to_int(ch);

            /* Apply decryption formula: P = a_inv * (C - b) mod 26. */
            int p = mod26(a_inv * (c - b));

            /* Convert numeric result back to letter. */
            plaintext[i] = int_to_char(p);
        }
        else {
            /* Preserve non-letters unchanged. */
            plaintext[i] = ciphertext[i];
        }

        i++;
    }

    /* Null-terminate output string. */
    plaintext[i] = '\0';
}
