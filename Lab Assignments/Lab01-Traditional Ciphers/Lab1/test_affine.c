/*
 * Test cases for the Affine cipher.
 */

#include <stdio.h>
#include "test_affine.h"
#include "affine.h"

void run_affine_tests(void)
{
    char ciphertext[256];
    char decrypted[256];

    printf("========================================\n");
    printf(" Affine Cipher - Test Cases\n");
    printf("========================================\n\n");

    // Test 1 (Classic known example)
    {
        const char* plaintext = "HELLO";
        int a = 5;
        int b = 8;
        const char* expected = "RCLLA";

        affine_encrypt(plaintext, ciphertext, a, b);
        affine_decrypt(ciphertext, decrypted, a, b);

        printf("Test 1 (Classic)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("a, b      : %d, %d\n", a, b);
        printf("Expected  : %s\n", expected);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // Test 2 (Mixed case + punctuation)
    {
        const char* plaintext = "Hello, World!";
        int a = 5;
        int b = 8;

        affine_encrypt(plaintext, ciphertext, a, b);
        affine_decrypt(ciphertext, decrypted, a, b);

        printf("Test 2 (Mixed case + punctuation)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("a, b      : %d, %d\n", a, b);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // Test 3 (Digits + spaces)
    {
        const char* plaintext = "CSCD 463 is fun";
        int a = 7;   // valid (coprime with 26)
        int b = 2;

        affine_encrypt(plaintext, ciphertext, a, b);
        affine_decrypt(ciphertext, decrypted, a, b);

        printf("Test 3 (Digits + spaces)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("a, b      : %d, %d\n", a, b);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }
}
