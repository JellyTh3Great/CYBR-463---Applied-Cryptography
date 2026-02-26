/*
 * task3_swap.c
 *
 * Purpose:
 *   Swaps the left and right halves of an n-bit word.
 *
 * Why this is nice:
 *   Instead of re-doing the bit math here, we reuse:
 *     - Task 1 (split_word) to break the word into halves
 *     - Task 2 (combine_halves) to rebuild it in swapped order
 *
 * Example (nbits = 8):
 *   word = 240  -> 11110000
 *   left = 1111 (15), right = 0000 (0)
 *   swap -> 00001111 (15)
 */

#include "task3_swap.h"
#include "task1_split.h"
#include "task2_combine.h"

uint32_t swap_halves(uint32_t word, int nbits)
{
    /* These will hold the two halves after splitting */
    uint32_t L = 0;
    uint32_t R = 0;

    /* Step 1: Split the word into left half (L) and right half (R) */
    split_word(word, nbits, &L, &R);

    /* Step 2: Combine them back together in reverse order (R becomes the new left) */
    return combine_halves(R, L, nbits);
}
