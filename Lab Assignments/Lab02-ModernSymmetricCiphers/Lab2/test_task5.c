#include <stdio.h>
#include <stdint.h>

#include "utils.h"
#include "task5_pbox.h"
#include "test_task5.h"

static void print_case_header(int n) {
    printf("\n--- Test Case %d ---\n", n);
}

void run_task5_tests(void)
{
    printf("\n==============================\n");
    printf(" Task 5 Tests: P-box Permute\n");
    printf("==============================\n");

    // Test Case 1 (Corrected PDF)
    // Input: 202 (11001010)
    // T = [5,6,1,4,3,7,8,2]
    // Output: 165 (10100101)
    {
        print_case_header(1);
        uint32_t in = 202;
        int T[8] = { 5,6,1,4,3,7,8,2 };
        uint32_t out = pbox_permute(in, T, 8);

        printf("Input:  %u (", in);  print_bin(in, 8);  printf(")\n");
        printf("T = [5,6,1,4,3,7,8,2]\n");
        printf("Output: %u (", out); print_bin(out, 8); printf(")\n");
        printf("Expected Output=165 (10100101)\n");
    }

    // Test Case 2: Identity permutation -> output should equal input
    {
        print_case_header(2);
        uint32_t in = 202;
        int T[8] = { 1,2,3,4,5,6,7,8 };
        uint32_t out = pbox_permute(in, T, 8);

        printf("Input:  %u (", in);  print_bin(in, 8);  printf(")\n");
        printf("T = [1,2,3,4,5,6,7,8]\n");
        printf("Output: %u (", out); print_bin(out, 8); printf(")\n");
        printf("Expected Output=202 (11001010)\n");
    }

    // Test Case 3: Reverse bits permutation
    // T = [8,7,6,5,4,3,2,1]
    // 202 (11001010) reversed -> 01010011 = 83
    {
        print_case_header(3);
        uint32_t in = 202;
        int T[8] = { 8,7,6,5,4,3,2,1 };
        uint32_t out = pbox_permute(in, T, 8);

        printf("Input:  %u (", in);  print_bin(in, 8);  printf(")\n");
        printf("T = [8,7,6,5,4,3,2,1]\n");
        printf("Output: %u (", out); print_bin(out, 8); printf(")\n");
        printf("Expected Output=83 (01010011)\n");
    }
}
