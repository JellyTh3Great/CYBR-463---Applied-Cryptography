/*
 * main.c (Lab 2)
 *
 * Menu-driven launcher for all tasks.
 * Structure:
 *   Main Menu: pick task
 *   Submenu:
 *     1) Run function (custom input)
 *     2) Run test cases (PDF example + 2 additional cases)
 *     0) Back
 *
 * Notes:
 * - Uses fgets + strtol for safe input (no scanf warnings).
 * - "Run test cases" calls run_taskX_tests() from the test files.
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "task1_split.h"
#include "task2_combine.h"
#include "task3_swap.h"
#include "task4_rotate.h"
#include "task5_pbox.h"
#include "task6_invperm.h"

 /* Test headers (these should expose run_taskX_tests()) */
#include "test_task1.h"
#include "test_task2.h"
#include "test_task3.h"
#include "test_task4.h"
#include "test_task5.h"
#include "test_task6.h"

/* ---------------- Input helpers (Lab 1 style) ---------------- */

static void read_line(const char* prompt, char* buf, int buf_size)
{
    printf("%s", prompt);

    if (fgets(buf, buf_size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }

    size_t n = strlen(buf);
    if (n > 0 && buf[n - 1] == '\n') {
        buf[n - 1] = '\0';
    }
}

static int read_int(const char* prompt)
{
    char line[64];

    while (1) {
        read_line(prompt, line, (int)sizeof(line));

        char* endptr = NULL;
        long val = strtol(line, &endptr, 10);

        if (endptr != line) {
            return (int)val;
        }

        printf("Please enter a valid integer.\n");
    }
}

static void pause_enter(void)
{
    char tmp[8];
    read_line("\nPress ENTER to continue...", tmp, (int)sizeof(tmp));
}

static int read_task_submenu_choice(void)
{
    while (1) {
        printf("\n--- Submenu ---\n");
        printf("1) Run function\n");
        printf("2) Run test cases\n");
        printf("0) Back\n");
        int choice = read_int("Select: ");
        if (choice == 0 || choice == 1 || choice == 2) return choice;
        printf("Invalid choice.\n");
    }
}

/* ---------------- Task 1: Split ---------------- */

static void task1_run_function(void)
{
    int nbits = read_int("Enter nbits (even and between 2-32): ");
    if (nbits <= 0 || (nbits % 2) != 0 || nbits > 32) {
        printf("nbits must be even and between 2 and 32.\n");
        return;
    }

    uint32_t word = (uint32_t)read_int("Enter word (decimal): ");

    uint32_t L = 0, R = 0;
    split_word(word, nbits, &L, &R);

    printf("\nTask1 Split Result:\n");
    printf("Input:  %u (", word); print_bin(word, nbits); printf(")\n");
    printf("Left:   %u (", L);    print_bin(L, nbits / 2); printf(")\n");
    printf("Right:  %u (", R);    print_bin(R, nbits / 2); printf(")\n");
}

/* ---------------- Task 2: Combine ---------------- */

static void task2_run_function(void)
{
    int nbits = read_int("Enter nbits (even and between 2-32): ");
    if (nbits <= 0 || (nbits % 2) != 0 || nbits > 32) {
        printf("nbits must be even and between 2 and 32.\n");
        return;
    }

    int half = nbits / 2;

    uint32_t left = (uint32_t)read_int("Enter LEFT half (decimal): ");
    uint32_t right = (uint32_t)read_int("Enter RIGHT half (decimal): ");

    uint32_t out = combine_halves(left, right, nbits);

    printf("\nTask2 Combine Result:\n");
    printf("Left:   %u (", left);  print_bin(left, half); printf(")\n");
    printf("Right:  %u (", right); print_bin(right, half); printf(")\n");
    printf("Output: %u (", out);   print_bin(out, nbits); printf(")\n");
}

/* ---------------- Task 3: Swap ---------------- */

static void task3_run_function(void)
{
    int nbits = read_int("Enter nbits (even and between 2-32): ");
    if (nbits <= 0 || (nbits % 2) != 0 || nbits > 32) {
        printf("nbits must be even and between 2 and 32.\n");
        return;
    }

    uint32_t word = (uint32_t)read_int("Enter word (decimal): ");

    uint32_t out = swap_halves(word, nbits);

    printf("\nTask3 Swap Result:\n");
    printf("Input:  %u (", word); print_bin(word, nbits); printf(")\n");
    printf("Output: %u (", out);  print_bin(out, nbits); printf(")\n");
}

/* ---------------- Task 4: Rotate ---------------- */

static void task4_run_function(void)
{
    int nbits = read_int("Enter nbits (between 1-32): ");
    if (nbits <= 0 || nbits > 32) {
        printf("nbits must be between 1 and 32.\n");
        return;
    }

    uint32_t word = (uint32_t)read_int("Enter word (decimal): ");
    int dir = read_int("Direction: 1) Left  2) Right : ");
    int k = read_int("Enter shift amount k: ");

    uint32_t out = (dir == 2) ? rotr(word, nbits, k) : rotl(word, nbits, k);

    printf("\nTask4 Rotate Result:\n");
    printf("Input:  %u (", word); print_bin(word, nbits); printf(")\n");
    printf("Output: %u (", out);  print_bin(out, nbits); printf(")\n");
}

/* ---------------- Task 5: P-box ---------------- */

static void task5_run_function(void)
{
    uint32_t word = (uint32_t)read_int("Enter 8-bit input word (0-255): ");
    if (word > 255u) {
        printf("Input must be between 0 and 255.\n");
        return;
    }

    printf("Enter permutation table T[1..8] (each 1-8)\n");
    int T[8];
    for (int i = 0; i < 8; ++i) {
        char prompt[64];
        sprintf(prompt, "T[%d]: ", i + 1);
        T[i] = read_int(prompt);
        if (T[i] < 1 || T[i] > 8) {
            printf("Each T[i] must be between 1 and 8.\n");
            return;
        }
    }

    uint32_t out = pbox_permute(word, T, 8);

    printf("\nTask5 P-box Result:\n");
    printf("Input:  %u (", word); print_bin(word, 8); printf(")\n");
    printf("Output: %u (", out);  print_bin(out, 8); printf(")\n");
}

/* ---------------- Task 6: Invert permutation ---------------- */

static void task6_run_function(void)
{
    int n = read_int("Enter table size n (1-64): ");
    if (n <= 0 || n > 64) {
        printf("Please choose n between 1 and 64.\n");
        return;
    }

    int T[64];
    int inv[64];

    printf("Enter permutation table T[1..n] (each 1..n)\n");
    for (int i = 0; i < n; ++i) {
        char prompt[64];
        sprintf(prompt, "T[%d]: ", i + 1);
        T[i] = read_int(prompt);
        if (T[i] < 1 || T[i] > n) {
            printf("Each T[i] must be between 1 and %d.\n", n);
            return;
        }
    }

    invert_permutation(T, n, inv);

    printf("\nTask6 Inverse Result:\n");
    printf("T   = [");
    for (int i = 0; i < n; ++i) printf("%d%s", T[i], (i < n - 1) ? "," : "");
    printf("]\nInv = [");
    for (int i = 0; i < n; ++i) printf("%d%s", inv[i], (i < n - 1) ? "," : "");
    printf("]\n");
}

/* ---------------- Task modes (Lab 1 style) ---------------- */

static void run_task1_mode(void)
{
    int sub = read_task_submenu_choice();
    if (sub == 0) return;
    if (sub == 2) { run_task1_tests(); pause_enter(); }
    else { task1_run_function(); pause_enter(); }
}

static void run_task2_mode(void)
{
    int sub = read_task_submenu_choice();
    if (sub == 0) return;
    if (sub == 2) { run_task2_tests(); pause_enter(); }
    else { task2_run_function(); pause_enter(); }
}

static void run_task3_mode(void)
{
    int sub = read_task_submenu_choice();
    if (sub == 0) return;
    if (sub == 2) { run_task3_tests(); pause_enter(); }
    else { task3_run_function(); pause_enter(); }
}

static void run_task4_mode(void)
{
    int sub = read_task_submenu_choice();
    if (sub == 0) return;
    if (sub == 2) { run_task4_tests(); pause_enter(); }
    else { task4_run_function(); pause_enter(); }
}

static void run_task5_mode(void)
{
    int sub = read_task_submenu_choice();
    if (sub == 0) return;
    if (sub == 2) { run_task5_tests(); pause_enter(); }
    else { task5_run_function(); pause_enter(); }
}

static void run_task6_mode(void)
{
    int sub = read_task_submenu_choice();
    if (sub == 0) return;
    if (sub == 2) { run_task6_tests(); pause_enter(); }
    else { task6_run_function(); pause_enter(); }
}

/* ---------------- Main menu ---------------- */

int main(void)
{
    while (1) {
        printf("========================================\n");
        printf(" Lab 2 - Modern Symmetric Cipher Tasks\n");
        printf("========================================\n");
        printf("1) Task 1 - Split\n");
        printf("2) Task 2 - Combine\n");
        printf("3) Task 3 - Swap\n");
        printf("4) Task 4 - Rotate\n");
        printf("5) Task 5 - P-box Permute\n");
        printf("6) Task 6 - Invert Permutation\n");
        printf("0) Exit\n");

        int choice = read_int("Select a task: ");
        printf("\n");

        switch (choice) {
        case 1: run_task1_mode(); break;
        case 2: run_task2_mode(); break;
        case 3: run_task3_mode(); break;
        case 4: run_task4_mode(); break;
        case 5: run_task5_mode(); break;
        case 6: run_task6_mode(); break;
        case 0: printf("Goodbye!\n"); return 0;
        default:
            printf("Invalid choice.\n\n");
            break;
        }
    }
}
