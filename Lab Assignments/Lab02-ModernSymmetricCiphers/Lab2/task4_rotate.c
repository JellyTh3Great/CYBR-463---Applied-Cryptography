/*
 * task4_rotate.c
 *
 * Purpose:
 *   Performs bit rotations on an n-bit word.
 *
 * Two operations are provided:
 *   - rotl: rotate left
 *   - rotr: rotate right
 *
 * Key idea:
 *   A rotation shifts bits, but the bits that "fall off" one end
 *   wrap around and re-enter on the other end.
 *
 * Example (nbits = 4):
 *   word = 12 -> 1100
 *   rotl by 2 -> 0011 (3)
 */

#include "task4_rotate.h"
#include "utils.h"

 /*
  * Rotate LEFT by k positions within nbits
  */
uint32_t rotl(uint32_t word, int nbits, int k)
{
    /* Invalid bit-width means no meaningful rotation */
    if (nbits <= 0)
        return 0u;

    /*
     * Reduce k so it is within the range [0, nbits-1]
     * Example: rotating by 10 bits in a 4-bit word
     * is the same as rotating by 2 bits.
     */
    k %= nbits;
    if (k < 0)
        k += nbits;

    /*
     * Mask the word so only the lowest nbits are considered.
     * This prevents bits outside the range from interfering.
     */
    word = mask_n(word, nbits);

    /* Rotating by 0 bits changes nothing */
    if (k == 0)
        return word;

    /*
     * Perform the left rotation:
     *   - Left shift by k
     *   - Right shift by (nbits - k) to capture the wrap-around bits
     *   - OR the two parts together
     *   - Mask again to keep exactly nbits
     */
    return mask_n(
        (word << k) | (word >> (nbits - k)),
        nbits
    );
}

/*
 * Rotate RIGHT by k positions within nbits
 */
uint32_t rotr(uint32_t word, int nbits, int k)
{
    /* Invalid bit-width means no meaningful rotation */
    if (nbits <= 0)
        return 0u;

    /*
     * Normalize k so it fits within the bit-width.
     */
    k %= nbits;
    if (k < 0)
        k += nbits;

    /*
     * Keep only the lowest nbits of the word.
     */
    word = mask_n(word, nbits);

    /* No rotation needed if k is zero */
    if (k == 0)
        return word;

    /*
     * Perform the right rotation:
     *   - Right shift by k
     *   - Left shift by (nbits - k) to wrap bits around
     *   - Combine with OR
     *   - Mask to ensure exact nbit width
     */
    return mask_n(
        (word >> k) | (word << (nbits - k)),
        nbits
    );
}
