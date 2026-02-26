/*
 * vigenere.c
 *
 * Vigenère Cipher
 * ---------------
 * The Vigenère cipher is like a repeating Caesar cipher.
 * Instead of using one fixed shift, it uses a KEYWORD.
 * Each letter of the keyword determines the shift for one plaintext letter.
 *
 * Letter-to-number mapping:
 *   A -> 0, B -> 1, ..., Z -> 25
 *
 * Key letter -> shift:
 *   shift = key_letter_value
 *   Example: 'A' -> 0, 'B' -> 1, ..., 'Z' -> 25
 *
 * Encryption formula:
 *   C = (P + shift) mod 26
 *
 * Decryption formula:
 *   P = (C - shift) mod 26
 *
 * Small example:
 *   Plaintext:  "ABC"
 *   Key:        "KEY"  -> shifts: K=10, E=4, Y=24
 *   Encrypt:
 *     A(0)+10 = 10 -> K
 *     B(1)+4  = 5  -> F
 *     C(2)+24 = 0  -> A
 *   Ciphertext: "KFA"
 *
 * Input behavior for this project:
 * - Letters are encrypted/decrypted and output as uppercase.
 * - Non-letter characters in the MESSAGE are preserved unchanged.
 * - Non-letter characters in the KEY are ignored (only key letters create shifts).
 * - The key only advances when a plaintext/ciphertext character is a letter.
 *   (So spaces/punctuation do NOT consume key characters.)
 */

#include "vigenere.h"
#include "utils.h"

 /*
  * build_key_shifts(key, shifts, max_shifts)
  * -----------------------------------------
  * Converts the keyword into an array of numeric shifts (0..25).
  *
  * Why we do this:
  *   It’s easier/faster to work with integers than repeatedly converting
  *   key characters during encryption/decryption.
  *
  * Behavior:
  * - Reads the key string left to right.
  * - Keeps letters only (ignores digits/punctuation/spaces).
  * - Uppercases letters so mapping is consistent.
  * - Stores each letter as a shift value 0..25.
  *
  * Returns:
  * - number of shifts stored (key length in letters)
  * - if 0, the key contained no letters (cipher cannot operate)
  */
static int build_key_shifts(const char* key, int shifts[], int max_shifts)
{
    int count = 0;
    int i = 0;

    while (key[i] != '\0' && count < max_shifts) {
        if (is_alpha(key[i])) {
            char kch = to_upper(key[i]);     /* normalize to A-Z */
            shifts[count] = char_to_int(kch);/* store shift 0..25 */
            count++;
        }
        i++;
    }

    return count; /* 0 means: key had no letters */
}

/*
 * vigenere_encrypt(plaintext, ciphertext, key)
 * --------------------------------------------
 * Encrypts plaintext using the Vigenère cipher.
 *
 * Notes:
 * - We keep a separate counter 'k' to track how many LETTERS we have encrypted so far.
 * - This is important because we do NOT want punctuation/spaces to advance the key.
 */
void vigenere_encrypt(const char* plaintext, char* ciphertext, const char* key)
{
    int key_shifts[256];
    int key_len = build_key_shifts(key, key_shifts, 256);

    int i = 0;  /* index into plaintext/ciphertext strings */
    int k = 0;  /* counts ONLY letters processed (controls key position) */

    /* If the key has no letters, we cannot generate shifts -> copy safely */
    if (key_len == 0) {
        while (plaintext[i] != '\0') {
            ciphertext[i] = plaintext[i];
            i++;
        }
        ciphertext[i] = '\0';
        return;
    }

    while (plaintext[i] != '\0') {
        char ch = plaintext[i];

        if (is_alpha(ch)) {
            ch = to_upper(ch);

            /* Convert plaintext letter to number 0..25 */
            int p = char_to_int(ch);

            /* Pick the shift from the key (repeat key using modulo) */
            int shift = key_shifts[k % key_len];

            /* Encrypt: C = (P + shift) mod 26 */
            int c = (p + shift) % 26;

            ciphertext[i] = int_to_char(c);

            /* Advance key position ONLY when we encrypt a letter */
            k++;
        }
        else {
            /* Preserve non-letters exactly */
            ciphertext[i] = plaintext[i];
        }

        i++;
    }

    ciphertext[i] = '\0';
}

/*
 * vigenere_decrypt(ciphertext, plaintext, key)
 * --------------------------------------------
 * Decrypts ciphertext using the Vigenère cipher.
 *
 * Decryption reverses encryption by subtracting the same key shifts.
 * We again use 'k' so the key only advances on letters.
 */
void vigenere_decrypt(const char* ciphertext, char* plaintext, const char* key)
{
    int key_shifts[256];
    int key_len = build_key_shifts(key, key_shifts, 256);

    int i = 0;
    int k = 0;

    /* If the key has no letters, copy safely */
    if (key_len == 0) {
        while (ciphertext[i] != '\0') {
            plaintext[i] = ciphertext[i];
            i++;
        }
        plaintext[i] = '\0';
        return;
    }

    while (ciphertext[i] != '\0') {
        char ch = ciphertext[i];

        if (is_alpha(ch)) {
            ch = to_upper(ch);

            /* Convert ciphertext letter to number 0..25 */
            int c = char_to_int(ch);

            /* Repeat key shifts with modulo */
            int shift = key_shifts[k % key_len];

            /* Decrypt: P = (C - shift) mod 26
               Add 26 before % to avoid negative values */
            int p = (c - shift + 26) % 26;

            plaintext[i] = int_to_char(p);

            k++;
        }
        else {
            plaintext[i] = ciphertext[i];
        }

        i++;
    }

    plaintext[i] = '\0';
}
