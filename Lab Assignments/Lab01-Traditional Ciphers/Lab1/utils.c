/*
 * utils.c
 *
 * Common Utility Helpers for Classical Ciphers
 * --------------------------------------------
 * This file contains small helper functions used across all cipher
 * implementations (Caesar, Atbash, Vigenere, Affine, Playfair, Hill).
 *
 * Why these helpers exist:
 * - Most classical ciphers work by mapping letters to numbers:
 *     A -> 0, B -> 1, ..., Z -> 25
 * - We also need simple character checks and case normalization,
 *   but for this course we avoid using libraries like <ctype.h>.
 *
 * IMPORTANT ASSUMPTIONS:
 * - char_to_int() expects an UPPERCASE letter 'A'..'Z'
 *   (so callers usually run to_upper() first)
 * - is_alpha() checks BOTH uppercase and lowercase letters
 */

#include "utils.h"

 /*
  * char_to_int(c)
  * --------------
  * Converts an uppercase letter to its alphabet index (0..25).
  *
  * Example:
  *   'A' -> 0
  *   'B' -> 1
  *   ...
  *   'Z' -> 25
  *
  * Precondition:
  *   c should be in the range 'A'..'Z'.
  *   (If you have lowercase input, call to_upper(c) first.)
  */
int char_to_int(char c)
{
    return c - 'A';
}

/*
 * int_to_char(i)
 * --------------
 * Converts a number (0..25) back into an uppercase letter.
 *
 * Example:
 *   0  -> 'A'
 *   1  -> 'B'
 *   ...
 *   25 -> 'Z'
 *
 * Precondition:
 *   i should be in the range 0..25.
 */
char int_to_char(int i)
{
    return (char)(i + 'A');
}

/*
 * is_alpha(c)
 * -----------
 * Checks whether a character is a letter (A-Z or a-z).
 *
 * Returns:
 *   1 if c is alphabetic
 *   0 otherwise
 *
 * Note:
 *   This function does NOT treat digits or punctuation as letters.
 */
int is_alpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

/*
 * to_upper(c)
 * -----------
 * Converts a lowercase letter to uppercase.
 *
 * Behavior:
 * - If c is in 'a'..'z', it returns the uppercase version.
 * - If c is already uppercase or is not a letter, it returns c unchanged.
 *
 * Why we need this:
 * - Our ciphers typically output uppercase letters for consistency.
 * - It also makes letter-to-number mapping (A=0..Z=25) predictable.
 */
char to_upper(char c)
{
    if (c >= 'a' && c <= 'z') {
        /* Difference between lowercase and uppercase ASCII letters is constant:
           'a' - 'A' == 32 */
        return c - ('a' - 'A');
    }
    return c;
}