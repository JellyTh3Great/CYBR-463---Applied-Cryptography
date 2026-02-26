#include <stdio.h>
#include <stdint.h>

#include "utils.h"
#include "task3_swap.h"
#include "test_task3.h"

static void print_case_header(int n) {
    printf("\n--- Test Case %d ---\n", n);
}

void run_task3_tests(void)
{
    printf("\n==============================\n");
    printf(" Task 3 Tests: Swap\n");
    printf("==============================\n");

    // Test Case 1 (PDF): swap(240,8) -> 15
    {
        print_case_header(1);
        uint32_t in = 240;
        uint32_t out = swap_halves(in, 8);

        printf("Input:  %u (", in);  print_bin(in, 8);  printf(")\n");
        printf("Output: %u (", out); print_bin(out, 8); printf(")\n");
        printf("Expected Output=15 (00001111)\n");
    }

    // Test Case 2: swap(15,8) -> 240
    {
        print_case_header(2);
        uint32_t in = 15;
        uint32_t out = swap_halves(in, 8);

        printf("Input:  %u (", in);  print_bin(in, 8);  printf(")\n");
        printf("Output: %u (", out); print_bin(out, 8); printf(")\n");
        printf("Expected Output=240 (11110000)\n");
    }

    // Test Case 3: swap(8004,16) -> 17439
    {
        print_case_header(3);
        uint32_t in = 8004;
        uint32_t out = swap_halves(in, 16);

        printf("Input:  %u (", in);  print_bin(in, 16);  printf(")\n");
        printf("Output: %u (", out); print_bin(out, 16); printf(")\n");
        printf("Expected Output=17439 (0100010000011111)\n");
    }
}
