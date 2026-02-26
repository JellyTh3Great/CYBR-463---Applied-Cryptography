/*
 * task2_combine.c
 *
 * Purpose:
 *   Combines two equal-sized halves into a single n-bit word.
 *   This is the inverse operation of Task 1 (Split).
 *
 * Example (nbits = 8):
 *   left  = 15  -> 1111
 *   right = 0   -> 0000
 *   result      -> 11110000 (240)
 *
 * Parameters:
 *   left   - The left half (most significant bits)
 *   right  - The right half (least significant bits)
 *   nbits  - Total number of bits in the final result (must be even)
 *
 * Returns:
 *   A single n-bit value formed by joining left and right
 */

#include "task2_combine.h"
#include "utils.h"

uint32_t combine_halves(uint32_t left, uint32_t right, int nbits)
{
    /*
     * Each half is exactly half of the total bit-width.
     * Example: nbits = 16 → half = 8
     */
    int half = nbits / 2;

    /*
     * Create a mask that keeps only 'half' bits.
     * Example: half = 4 → mask = 0000 1111
     *
     * This ensures that extra bits in 'left' or 'right'
     * do not leak into the final result.
     */
    uint32_t half_mask =
        (half >= 32) ? 0xFFFFFFFFu : ((1u << half) - 1u);

    /*
     * Build the combined value:
     *
     * 1) Mask the left half and shift it into the upper position
     * 2) Mask the right half and place it in the lower position
     * 3) OR the two parts together
     */
    uint32_t out =
        ((left & half_mask) << half) | (right & half_mask);

    /*
     * Finally, mask the result to exactly nbits.
     * This keeps the output clean and predictable.
     */
    return mask_n(out, nbits);
}
