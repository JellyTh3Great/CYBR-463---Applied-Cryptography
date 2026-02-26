/*
 * atbash.c
 *
 * Atbash Cipher
 * -------------
 * The Atbash cipher is a substitution cipher with a fixed mapping:
 *   A <-> Z, B <-> Y, C <-> X, ... , M <-> N
 *
 * Numeric view (A=0 .. Z=25):
 *   P = plaintext letter value
 *   C = 25 - P
 *
 * Small example:
 *   'A' -> P=0  => C=25 -> 'Z'
 *   'B' -> P=1  => C=24 -> 'Y'
 *   'Z' -> P=25 => C=0  -> 'A'
 *
 * Properties:
 * - No key is required.
 * - Encryption and decryption are the same operation (same mapping both ways).
 * - For this project: non-alphabetic characters are copied unchanged.
 * - We normalize letters to uppercase so output is consistent.
 */

#include "atbash.h"
#include "utils.h"

 /*
  * atbash_encrypt(plaintext, ciphertext)
  * -----------------------------------
  * Encrypts a plaintext string using Atbash and stores the result in ciphertext.
  *
  * Rules in this implementation:
  * - If the character is a letter: convert to uppercase, apply Atbash mapping.
  * - If the character is NOT a letter: copy it as-is (spaces/punctuation/digits).
  */
void atbash_encrypt(const char* plaintext, char* ciphertext)
{
    int i = 0;

    /* Walk through the input string until we hit the null terminator '\0'. */
    while (plaintext[i] != '\0') {

        char ch = plaintext[i];

        if (is_alpha(ch)) {

            /* Normalize to uppercase so our A=0..Z=25 mapping is consistent. */
            ch = to_upper(ch);

            /* Convert 'A'..'Z' into a number 0..25. (Example: 'C' -> 2) */
            int p = char_to_int(ch);

            /* Atbash mapping: mirror around the center of the alphabet.
               Example: p=2 ('C') => c=25-2=23 ('X') */
            int c = 25 - p;

            /* Convert numeric result back into a letter 'A'..'Z'. */
            ciphertext[i] = int_to_char(c);
        }
        else {
            /* Leave non-letters unchanged. */
            ciphertext[i] = plaintext[i];
        }

        i++;
    }

    /* Always null-terminate output so it is a valid C string. */
    ciphertext[i] = '\0';
}

/*
 * atbash_decrypt(ciphertext, plaintext)
 * ------------------------------------
 * Decrypts a ciphertext string using Atbash.
 *
 * Important note:
 *   Atbash decryption is the exact same operation as encryption because the mapping is symmetric.
 *   (Applying the mirror mapping twice returns the original letter.)
 *
 * Even though it’s the same logic, we keep a separate function for clarity and consistency
 * with the other ciphers.
 */
void atbash_decrypt(const char* ciphertext, char* plaintext)
{
    int i = 0;

    while (ciphertext[i] != '\0') {

        char ch = ciphertext[i];

        if (is_alpha(ch)) {

            /* Normalize to uppercase before mapping. */
            ch = to_upper(ch);

            /* Convert 'A'..'Z' into 0..25. */
            int c = char_to_int(ch);

            /* Reverse mapping is identical: p = 25 - c. */
            int p = 25 - c;

            /* Convert numeric value back into a letter. */
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
