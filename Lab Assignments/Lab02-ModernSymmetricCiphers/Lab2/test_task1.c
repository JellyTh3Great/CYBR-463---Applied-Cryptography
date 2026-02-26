#include <stdio.h>
#include <stdint.h>

#include "utils.h"
#include "task1_split.h"
#include "test_task1.h"

static void print_case_header(int n) {
    printf("\n--- Test Case %d ---\n", n);
}

void run_task1_tests(void)
{
    printf("\n==============================\n");
    printf(" Task 1 Tests: Split\n");
    printf("==============================\n");

    // Test Case 1 (PDF)
    // 240 (11110000) -> L=15 (1111), R=0 (0000)
    {
        print_case_header(1);
        uint32_t word = 240, L = 0, R = 0;
        split_word(word, 8, &L, &R);

        printf("Input:  %u (", word); print_bin(word, 8); printf(")\n");
        printf("Left:   %u (", L);    print_bin(L, 4);     printf(")\n");
        printf("Right:  %u (", R);    print_bin(R, 4);     printf(")\n");
        printf("Expected Left=15, Right=0\n");
    }

    // Test Case 2
    // 8004 in 16 bits -> left 31, right 68
    {
        print_case_header(2);
        uint32_t word = 8004, L = 0, R = 0;
        split_word(word, 16, &L, &R);

        printf("Input:  %u (", word); print_bin(word, 16); printf(")\n");
        printf("Left:   %u (", L);    print_bin(L, 8);      printf(")\n");
        printf("Right:  %u (", R);    print_bin(R, 8);      printf(")\n");
        printf("Expected Left=31, Right=68\n");
    }

    // Test Case 3: all-ones in 8 bits
    // 255 (11111111) -> left 15, right 15
    {
        print_case_header(3);
        uint32_t word = 255, L = 0, R = 0;
        split_word(word, 8, &L, &R);

        printf("Input:  %u (", word); print_bin(word, 8); printf(")\n");
        printf("Left:   %u (", L);    print_bin(L, 4);     printf(")\n");
        printf("Right:  %u (", R);    print_bin(R, 4);     printf(")\n");
        printf("Expected Left=15, Right=15\n");
    }
}
