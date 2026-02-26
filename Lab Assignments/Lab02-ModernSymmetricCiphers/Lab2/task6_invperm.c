/*
 * task6_invperm.c
 *
 * Purpose:
 *   Computes the inverse of a permutation table.
 *
 * What "inverse permutation" means:
 *   If the original permutation T rearranges positions,
 *   the inverse permutation undoes that rearrangement.
 *
 * In other words:
 *   Applying T and then applying inv(T) returns everything
 *   back to its original position.
 *
 * Example:
 *   T    = [6, 3, 4, 5, 2, 1]
 *   Inv  = [6, 5, 2, 3, 4, 1]
 *
 * Because:
 *   - T[1] = 6  → Inv[6] = 1
 *   - T[2] = 3  → Inv[3] = 2
 *   - ...
 */

#include "task6_invperm.h"

void invert_permutation(const int* T, int n, int* inv_out)
{
    /*
     * Initialize the output array.
     * This isn't strictly required for correctness here,
     * but it keeps the result predictable and clean.
     */
    for (int i = 0; i < n; ++i) {
        inv_out[i] = 0;
    }

    /*
     * Build the inverse permutation.
     *
     * Lab convention:
     *   - T is a permutation of numbers 1..n
     *   - T[i] tells us which input position goes to output position i
     *
     * To invert this:
     *   If output position i takes input position T[i],
     *   then inverse[T[i]] must equal i.
     *
     * Note:
     *   - Loop variable i is 1-based to match the lab description
     *   - Array indexing is adjusted for C's 0-based arrays
     */
    for (int i = 1; i <= n; ++i) {
        int val = T[i - 1];   /* val is in the range 1..n */

        /* Place i in the inverse position */
        inv_out[val - 1] = i;
    }
}
