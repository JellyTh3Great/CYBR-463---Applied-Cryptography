#include <stdio.h>
#include <stdint.h>

#include "utils.h"
#include "task2_combine.h"
#include "test_task2.h"

static void print_case_header(int n) {
    printf("\n--- Test Case %d ---\n", n);
}

void run_task2_tests(void)
{
    printf("\n==============================\n");
    printf(" Task 2 Tests: Combine\n");
    printf("==============================\n");

    // Test Case 1 (PDF): combine(15,0,8) -> 240
    {
        print_case_header(1);
        uint32_t left = 15, right = 0;
        uint32_t out = combine_halves(left, right, 8);

        printf("Left:   %u (", left);  print_bin(left, 4);  printf(")\n");
        printf("Right:  %u (", right); print_bin(right, 4); printf(")\n");
        printf("Output: %u (", out);   print_bin(out, 8);   printf(")\n");
        printf("Expected Output=240 (11110000)\n");
    }

    // Test Case 2: combine(0,15,8) -> 15
    {
        print_case_header(2);
        uint32_t left = 0, right = 15;
        uint32_t out = combine_halves(left, right, 8);

        printf("Left:   %u (", left);  print_bin(left, 4);  printf(")\n");
        printf("Right:  %u (", right); print_bin(right, 4); printf(")\n");
        printf("Output: %u (", out);   print_bin(out, 8);   printf(")\n");
        printf("Expected Output=15 (00001111)\n");
    }

    // Test Case 3: combine(31,68,16) -> 8004
    {
        print_case_header(3);
        uint32_t left = 31, right = 68;
        uint32_t out = combine_halves(left, right, 16);

        printf("Left:   %u (", left);  print_bin(left, 8);   printf(")\n");
        printf("Right:  %u (", right); print_bin(right, 8);  printf(")\n");
        printf("Output: %u (", out);   print_bin(out, 16);   printf(")\n");
        printf("Expected Output=8004 (0001111101000100)\n");
    }
}