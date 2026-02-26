/*
 * task5_pbox.c
 *
 * Purpose:
 *   Applies a P-box (permutation box) to an n-bit input word.
 *
 * What a P-box does:
 *   It rearranges (permutes) the bits of the input according to a table T.
 *   No bits are changed from 0 to 1 or 1 to 0 — they are only moved around.
 *
 * Bit numbering convention (matches the lab):
 *   Bits are numbered 1..nbits from MSB -> LSB
 *     - Bit 1 is the MOST significant bit (leftmost)
 *     - Bit nbits is the LEAST significant bit (rightmost)
 *
 * Permutation rule:
 *   Output bit i comes from input bit T[i]
 *
 * Example idea:
 *   If T[1] = 5, then output bit 1 is copied from input bit 5.
 */

#include "task5_pbox.h"
#include "utils.h"

uint32_t pbox_permute(uint32_t word, const int* T, int nbits)
{
    /* This will hold the permuted result */
    uint32_t out = 0u;

    /*
     * Only consider the lowest nbits of the input.
     * (If word is larger than nbits, we ignore extra upper bits.)
     */
    word = mask_n(word, nbits);

    /*
     * We build the output one bit at a time.
     *
     * Loop variable i represents the OUTPUT bit position (1..nbits),
     * where 1 is the MSB and nbits is the LSB (lab convention).
     */
    for (int i = 1; i <= nbits; ++i) {

        /*
         * Find which INPUT bit should be copied into output bit i.
         * T is stored in a normal C array (0-based index),
         * but the bit positions in the lab are 1-based.
         *
         * So:
         *   output bit i uses input bit src = T[i-1]
         */
        int src = T[i - 1];   /* src is in the range 1..nbits */

        /*
         * Our C shift operations count bits from the LSB side (right side),
         * so we convert "src from MSB numbering" into "shift amount from LSB".
         *
         * If src = 1 (MSB), we want to shift by nbits-1.
         * If src = nbits (LSB), we want to shift by 0.
         */
        int in_from_lsb = nbits - src;

        /* Extract that single bit (0 or 1) from the input word */
        uint32_t bit = (word >> in_from_lsb) & 1u;

        /*
         * Now place that bit into the correct OUTPUT position.
         * Output bit positions are also numbered from MSB -> LSB,
         * so we do the same conversion for output position i.
         */
        int out_from_lsb = nbits - i;

        /* Set that bit in the output word */
        out |= (bit << out_from_lsb);
    }

    /*
     * Return only the lowest nbits of the output (clean result).
     */
    return mask_n(out, nbits);
}
