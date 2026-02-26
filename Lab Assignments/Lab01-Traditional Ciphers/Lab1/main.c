/*
 * main.c
 *
 * Menu-driven launcher for all ciphers.
 * Structure:
 *   Main Menu: pick cipher
 *   Submenu: (1) Run cipher (encrypt/decrypt) (2) Run test cases
 *
 * Notes:
 * - Uses fgets for safe input (no scanf headaches).
 * - Uses simple helper functions to read ints and lines.
 * - Playfair/Hill (as implemented) strip non-letters.
 */

#include <stdio.h>
#include <string.h>

 /* Cipher headers */
#include "caesar.h"
#include "atbash.h"
#include "vigenere.h"
#include "affine.h"
#include "playfair.h"
#include "hill.h"

/* Test headers */
#include "test_caesar.h"
#include "test_atbash.h"
#include "test_vigenere.h"
#include "test_affine.h"
#include "test_playfair.h"
#include "test_hill.h"

/* ---------------- Input helpers ---------------- */

/* Read a full line into buffer and strip trailing newline */
static void read_line(const char* prompt, char* buf, int buf_size)
{
    printf("%s", prompt);

    if (fgets(buf, buf_size, stdin) == NULL) {
        /* If input fails, just make it empty */
        buf[0] = '\0';
        return;
    }

    /* Remove trailing newline if present */
    size_t n = strlen(buf);
    if (n > 0 && buf[n - 1] == '\n') {
        buf[n - 1] = '\0';
    }
}

/* Read an integer from the user (re-prompts until it can parse one) */
static int read_int(const char* prompt)
{
    char line[64];

    while (1) {
        read_line(prompt, line, (int)sizeof(line));

        char* endptr = NULL;
        long val = strtol(line, &endptr, 10);

        /* endptr == line means: no digits were found */
        if (endptr != line) {
            return (int)val;
        }

        printf("Please enter a valid integer.\n");
    }
}

/* Simple yes/no choice for encrypt/decrypt */
static int read_encrypt_or_decrypt(void)
{
    while (1) {
        int choice = read_int("Choose: 1) Encrypt  2) Decrypt : ");
        if (choice == 1 || choice == 2) return choice;
        printf("Invalid choice.\n");
    }
}

/* Submenu choice: run cipher vs tests */
static int read_cipher_submenu_choice(void)
{
    while (1) {
        printf("\n--- Submenu ---\n");
        printf("1) Run cipher (encrypt/decrypt)\n");
        printf("2) Run test cases\n");
        printf("0) Back\n");
        int choice = read_int("Select: ");
        if (choice == 0 || choice == 1 || choice == 2) return choice;
        printf("Invalid choice.\n");
    }
}

/* ---------------- Run modes per cipher ---------------- */

/* IMPORTANT:
 * If your function names differ, just rename the calls below to match your .h files.
 * The menu structure stays the same.
 */

static void run_caesar_mode(void)
{
    int sub = read_cipher_submenu_choice();
    if (sub == 0) return;

    if (sub == 2) {
        run_caesar_tests();
        return;
    }

    /* Run cipher */
    char input[512];
    char output[512];

    int encdec = read_encrypt_or_decrypt();
    int key = read_int("Enter key (integer shift): ");
    read_line("Enter text: ", input, (int)sizeof(input));

    if (encdec == 1) {
        caesar_encrypt(input, output, key);
        printf("\nEncrypted : %s\n\n", output);
    }
    else {
        caesar_decrypt(input, output, key);
        printf("\nDecrypted : %s\n\n", output);
    }
}

static void run_atbash_mode(void)
{
    int sub = read_cipher_submenu_choice();
    if (sub == 0) return;

    if (sub == 2) {
        run_atbash_tests();
        return;
    }

    char input[512];
    char output[512];

    int encdec = read_encrypt_or_decrypt();
    read_line("Enter text: ", input, (int)sizeof(input));

    /* Atbash encrypt/decrypt are the same transformation,
       but we keep both calls for clarity. */
    if (encdec == 1) {
        atbash_encrypt(input, output);
        printf("\nEncrypted : %s\n\n", output);
    }
    else {
        atbash_decrypt(input, output);
        printf("\nDecrypted : %s\n\n", output);
    }
}

static void run_vigenere_mode(void)
{
    int sub = read_cipher_submenu_choice();
    if (sub == 0) return;

    if (sub == 2) {
        run_vigenere_tests();
        return;
    }

    char input[512];
    char output[512];
    char key[128];

    int encdec = read_encrypt_or_decrypt();
    read_line("Enter key (letters): ", key, (int)sizeof(key));
    read_line("Enter text: ", input, (int)sizeof(input));

    if (encdec == 1) {
        vigenere_encrypt(input, output, key);
        printf("\nEncrypted : %s\n\n", output);
    }
    else {
        vigenere_decrypt(input, output, key);
        printf("\nDecrypted : %s\n\n", output);
    }
}

static void run_affine_mode(void)
{
    int sub = read_cipher_submenu_choice();
    if (sub == 0) return;

    if (sub == 2) {
        run_affine_tests();
        return;
    }

    char input[512];
    char output[512];

    int encdec = read_encrypt_or_decrypt();
    int a = read_int("Enter a (must be invertible mod 26, e.g. 5,7,11,17,25): ");
    int b = read_int("Enter b: ");
    read_line("Enter text: ", input, (int)sizeof(input));

    if (encdec == 1) {
        affine_encrypt(input, output, a, b);
        printf("\nEncrypted : %s\n\n", output);
    }
    else {
        affine_decrypt(input, output, a, b);
        printf("\nDecrypted : %s\n\n", output);
    }
}

static void run_playfair_mode(void)
{
    int sub = read_cipher_submenu_choice();
    if (sub == 0) return;

    if (sub == 2) {
        run_playfair_tests();
        return;
    }

    char input[512];
    char output[512];
    char key[128];

    int encdec = read_encrypt_or_decrypt();
    read_line("Enter key (letters): ", key, (int)sizeof(key));
    read_line("Enter text: ", input, (int)sizeof(input));

    if (encdec == 1) {
        playfair_encrypt(input, output, key);
        printf("\nEncrypted : %s\n", output);
        printf("Note      : Playfair strips non-letters (5x5 version).\n\n");
    }
    else {
        playfair_decrypt(input, output, key);
        printf("\nDecrypted : %s\n", output);
        printf("Note      : Playfair strips non-letters (5x5 version).\n\n");
    }
}

static void run_hill_mode(void)
{
    int sub = read_cipher_submenu_choice();
    if (sub == 0) return;

    if (sub == 2) {
        run_hill_tests();
        return;
    }

    char input[512];
    char output[512];

    int encdec = read_encrypt_or_decrypt();

    /* Read 2x2 key matrix */
    int K[2][2];
    printf("Enter 2x2 key matrix values (integers):\n");
    K[0][0] = read_int("K[0][0]: ");
    K[0][1] = read_int("K[0][1]: ");
    K[1][0] = read_int("K[1][0]: ");
    K[1][1] = read_int("K[1][1]: ");

    read_line("Enter text: ", input, (int)sizeof(input));

    if (encdec == 1) {
        hill_encrypt_2x2(input, output, K);
        printf("\nEncrypted : %s\n", output);
        printf("Note      : Hill strips non-letters (in this implementation).\n\n");
    }
    else {
        hill_decrypt_2x2(input, output, K);
        printf("\nDecrypted : %s\n", output);
        printf("Note      : Hill strips non-letters (in this implementation).\n\n");
    }
}

/* ---------------- Main menu ---------------- */

int main(void)
{
    while (1) {
        printf("========================================\n");
        printf(" Traditional Ciphers - Main Menu\n");
        printf("========================================\n");
        printf("1) Caesar\n");
        printf("2) Atbash\n");
        printf("3) Vigenere\n");
        printf("4) Affine\n");
        printf("5) Playfair\n");
        printf("6) Hill (2x2)\n");
        printf("0) Exit\n");

        int choice = read_int("Select a cipher: ");
        printf("\n");

        switch (choice) {
        case 1: run_caesar_mode();   break;
        case 2: run_atbash_mode();   break;
        case 3: run_vigenere_mode(); break;
        case 4: run_affine_mode();   break;
        case 5: run_playfair_mode(); break;
        case 6: run_hill_mode();     break;
        case 0: printf("Goodbye!\n"); return 0;
        default:
            printf("Invalid choice.\n\n");
            break;
        }
    }
}
