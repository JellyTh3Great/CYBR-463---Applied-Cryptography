/*
 * utils.c
 *
 * Purpose:
 *   Provides small helper functions used across multiple tasks.
 *
 * Why this file exists:
 *   - Avoids repeating common bit-manipulation code
 *   - Keeps task files focused on *what* they do, not low-level details
 *
 * Functions in this file:
 *   - mask_n  : Keeps only the lowest n bits of a value
 *   - print_bin : Prints a value in binary (for visualization/debugging)
 */

#include "utils.h"
#include <stdio.h>

 /*
  * mask_n
  *
  * Purpose:
  *   Returns the value x with only its lowest nbits preserved.
  *   All higher bits are cleared (set to 0).
  *
  * Examples:
  *   mask_n(255, 4) -> 15   (1111)
  *   mask_n(240, 8) -> 240  (11110000)
  *
  * Parameters:
  *   x      - Input value
  *   nbits  - Number of bits to keep
  *
  * Returns:
  *   The masked value
  */
uint32_t mask_n(uint32_t x, int nbits)
{
    /* No bits requested → result is zero */
    if (nbits <= 0)
        return 0u;

    /*
     * If nbits is 32 or more, the entire 32-bit value is valid,
     * so no masking is needed.
     */
    if (nbits >= 32)
        return x;

    /*
     * Create a mask with nbits set to 1.
     * Example: nbits = 5 → mask = 0001 1111
     *
     * AND-ing with the mask clears all higher bits.
     */
    return x & ((1u << nbits) - 1u);
}

/*
 * print_bin
 *
 * Purpose:
 *   Prints the binary representation of a value using exactly nbits.
 *
 * Important note:
 *   This function is for DISPLAY ONLY.
 *   It does not print newlines or spaces.
 *
 * Example:
 *   print_bin(5, 4) prints: 0101
 *
 * Parameters:
 *   x      - Value to print
 *   nbits  - Number of bits to display
 */
void print_bin(uint32_t x, int nbits)
{
    /*
     * Start from the most significant bit and work down to the least.
     * This makes the output match normal binary reading order.
     */
    for (int i = nbits - 1; i >= 0; --i) {

        /*
         * Shift the desired bit into the LSB position and test it.
         * Print '1' if the bit is set, otherwise print '0'.
         */
        putchar(((x >> i) & 1u) ? '1' : '0');
    }
}
