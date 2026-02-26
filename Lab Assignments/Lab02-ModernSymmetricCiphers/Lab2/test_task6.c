#include <stdio.h>

#include "task6_invperm.h"
#include "test_task6.h"

static void print_case_header(int n) {
    printf("\n--- Test Case %d ---\n", n);
}

static void print_table(const char* label, const int* a, int n) {
    printf("%s = [", label);
    for (int i = 0; i < n; ++i) {
        printf("%d%s", a[i], (i < n - 1) ? "," : "");
    }
    printf("]\n");
}

void run_task6_tests(void)
{
    printf("\n==============================\n");
    printf(" Task 6 Tests: Invert Permutation\n");
    printf("==============================\n");

    // Test Case 1 (PDF)
    // T=[6,3,4,5,2,1] -> inv=[6,5,2,3,4,1]
    {
        print_case_header(1);
        int T[6] = { 6,3,4,5,2,1 };
        int inv[6];
        invert_permutation(T, 6, inv);

        print_table("T", T, 6);
        print_table("Inv", inv, 6);
        printf("Expected Inv=[6,5,2,3,4,1]\n");
    }

    // Test Case 2: identity permutation -> inverse is itself
    {
        print_case_header(2);
        int T[6] = { 1,2,3,4,5,6 };
        int inv[6];
        invert_permutation(T, 6, inv);

        print_table("T", T, 6);
        print_table("Inv", inv, 6);
        printf("Expected Inv=[1,2,3,4,5,6]\n");
    }

    // Test Case 3: rotation permutation
    // T=[2,3,4,5,6,1] -> inv=[6,1,2,3,4,5]
    {
        print_case_header(3);
        int T[6] = { 2,3,4,5,6,1 };
        int inv[6];
        invert_permutation(T, 6, inv);

        print_table("T", T, 6);
        print_table("Inv", inv, 6);
        printf("Expected Inv=[6,1,2,3,4,5]\n");
    }
}
