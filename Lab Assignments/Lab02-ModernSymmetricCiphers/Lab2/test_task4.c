#include <stdio.h>
#include <stdint.h>

#include "utils.h"
#include "task4_rotate.h"
#include "test_task4.h"

static void print_case_header(int n) {
    printf("\n--- Test Case %d ---\n", n);
}

void run_task4_tests(void)
{
    printf("\n==============================\n");
    printf(" Task 4 Tests: Rotate\n");
    printf("==============================\n");

    // Test Case 1 (PDF): rotl(12,4,2) -> 3
    {
        print_case_header(1);
        uint32_t in = 12;
        uint32_t out = rotl(in, 4, 2);

        printf("Input:  %u (", in);  print_bin(in, 4);  printf(")\n");
        printf("rotl2:  %u (", out); print_bin(out, 4); printf(")\n");
        printf("Expected Output=3 (0011)\n");
    }

    // Test Case 2: rotr(12,4,1) -> 6
    {
        print_case_header(2);
        uint32_t in = 12;
        uint32_t out = rotr(in, 4, 1);

        printf("Input:  %u (", in);  print_bin(in, 4);  printf(")\n");
        printf("rotr1:  %u (", out); print_bin(out, 4); printf(")\n");
        printf("Expected Output=6 (0110)\n");
    }

    // Test Case 3: rotl(129,8,1) -> 3
    {
        print_case_header(3);
        uint32_t in = 129;
        uint32_t out = rotl(in, 8, 1);

        printf("Input:  %u (", in);  print_bin(in, 8);  printf(")\n");
        printf("rotl1:  %u (", out); print_bin(out, 8); printf(")\n");
        printf("Expected Output=3 (00000011)\n");
    }
}
