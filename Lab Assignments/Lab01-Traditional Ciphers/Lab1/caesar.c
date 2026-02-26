/*
 * caesar.c
 *
 * Caesar Cipher
 * -------------
 * The Caesar cipher is a shift-based substitution cipher.
 * Each letter in the plaintext is shifted by a fixed number of positions
 * forward (encryption) or backward (decryption) in the alphabet.
 *
 * Letter-to-number mapping:
 *   A -> 0, B -> 1, ..., Z -> 25
 *
 * Encryption formula:
 *   C = (P + key) mod 26
 *
 * Decryption formula:
 *   P = (C - key) mod 26
 *
 * Small example:
 *   Key = 3
 *   Plaintext letter: 'X' -> P = 23
 *   Encryption: (23 + 3) mod 26 = 0 -> 'A'
 *   Decryption: (0 - 3) mod 26 = 23 -> 'X'
 *
 * Input behavior for this project:
 *   - Alphabetic characters are encrypted/decrypted (case-insensitive; output is uppercase).
 *   - Non-alphabetic characters (spaces, punctuation, digits) are preserved unchanged.
 *   - Keys may be positive, negative, or larger than 26; modulo arithmetic handles wrap-around.
 */

#include "caesar.h"
#include "utils.h"

 /*
  * mod26(x)
  * --------
  * Normalizes an integer into the range [0..25].
  *
  * Why this is needed:
  *   In C, the % operator can return negative results.
  *   This function ensures wrap-around behaves correctly for negative shifts.
  */
static int mod26(int x)
{
    int r = x % 26;
    if (r < 0) r += 26;
    return r;
}

/*
 * caesar_encrypt(plaintext, ciphertext, key)
 * -----------------------------------------
 * Encrypts plaintext using a Caesar shift.
 *
 * Parameters:
 *   plaintext  - input string to encrypt
 *   ciphertext - output buffer for encrypted text
 *   key        - integer shift value (can be any integer)
 *
 * Behavior:
 *   - Letters are shifted by 'key' positions and written as uppercase.
 *   - Non-letter characters are copied unchanged.
 */
void caesar_encrypt(const char* plaintext, char* ciphertext, int key)
{
    int i = 0;

    /* Process each character until the null terminator is reached. */
    while (plaintext[i] != '\0') {

        char ch = plaintext[i];

        if (is_alpha(ch)) {

            /* Normalize to uppercase for consistent A=0..Z=25 mapping. */
            ch = to_upper(ch);

            /* Convert letter to numeric value 0..25. */
            int p = char_to_int(ch);

            /* Apply Caesar shift: C = (P + key) mod 26. */
            int c = mod26(p + key);

            /* Convert numeric value back into a letter. */
            ciphertext[i] = int_to_char(c);
        }
        else {
            /* Preserve non-letter characters unchanged. */
            ciphertext[i] = plaintext[i];
        }

        i++;
    }

    /* Null-terminate the output string. */
    ciphertext[i] = '\0';
}

/*
 * caesar_decrypt(ciphertext, plaintext, key)
 * -----------------------------------------
 * Decrypts ciphertext using a Caesar shift.
 *
 * Decryption reverses encryption by subtracting the key.
 *
 * Parameters:
 *   ciphertext - encrypted input string
 *   plaintext  - output buffer for decrypted text
 *   key        - integer shift value used during encryption
 */
void caesar_decrypt(const char* ciphertext, char* plaintext, int key)
{
    int i = 0;

    while (ciphertext[i] != '\0') {

        char ch = ciphertext[i];

        if (is_alpha(ch)) {

            /* Normalize to uppercase for consistent mapping. */
            ch = to_upper(ch);

            /* Convert letter to numeric value 0..25. */
            int c = char_to_int(ch);

            /* Reverse the Caesar shift: P = (C - key) mod 26. */
            int p = mod26(c - key);

            /* Convert numeric value back into a letter. */
            plaintext[i] = int_to_char(p);
        }
        else {
            /* Preserve non-letter characters unchanged. */
            plaintext[i] = ciphertext[i];
        }

        i++;
    }

    /* Null-terminate the output string. */
    plaintext[i] = '\0';
}
