/*
 * task1_split.c
 *
 * Purpose:
 *   Splits an n-bit word into two equal halves:
 *     - Left half  (most significant bits)
 *     - Right half (least significant bits)
 *
 * Example (nbits = 8):
 *   word = 240  -> 11110000
 *   left  = 1111 (15)
 *   right = 0000 (0)
 *
 * Parameters:
 *   word   - The input value to split
 *   nbits  - Total number of bits to consider (must be even)
 *   left   - Output pointer for the left half
 *   right  - Output pointer for the right half
 */

#include "task1_split.h"
#include "utils.h"

void split_word(uint32_t word, int nbits, uint32_t* left, uint32_t* right)
{
    /*
     * We split the word into two equal halves.
     * Example: nbits = 16 ? half = 8
     */
    int half = nbits / 2;

    /*
     * Create a bit mask that keeps only 'half' bits.
     * Example: half = 4 ? mask = 0000 1111
     *
     * The conditional handles safety for large shifts,
     * even though we limit nbits elsewhere.
     */
    uint32_t half_mask =
        (half >= 32) ? 0xFFFFFFFFu : ((1u << half) - 1u);

    /*
     * Mask the input word so we only consider the lowest nbits.
     * This prevents unexpected behavior if 'word' is larger
     * than what nbits allows.
     */
    word = mask_n(word, nbits);

    /*
     * Extract the LEFT (most significant) half:
     * - Shift right by 'half' bits
     * - Apply the mask to isolate exactly 'half' bits
     */
    *left = (word >> half) & half_mask;

    /*
     * Extract the RIGHT (least significant) half:
     * - Simply apply the mask
     */
    *right = word & half_mask;
}
