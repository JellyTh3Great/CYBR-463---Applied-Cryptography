/*
* Test cases for Atbash cipher.
* Atbash has no key and encryption/decryption are essentially the same mapping.
*/

#include <stdio.h>
#include "atbash.h"
#include "test_atbash.h"

void run_atbash_tests(void)
{
    char ciphertext[256];
    char decrypted[256];

    printf("========================================\n");
    printf(" Atbash Cipher - Test Cases\n");
    printf("========================================\n\n");

    // ---------------- Test 1 (Lab-style simple input) ----------------
    {
        const char* plaintext = "HELLO";
        const char* expected = "SVOOL"; // Example from the assignment PDF

        atbash_encrypt(plaintext, ciphertext);
        atbash_decrypt(ciphertext, decrypted);

        printf("Test 1 (Simple)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Expected  : %s\n", expected);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 2 (Mixed case + punctuation) ----------------
    {
        const char* plaintext = "Hello, World!";

        atbash_encrypt(plaintext, ciphertext);
        atbash_decrypt(ciphertext, decrypted);

        printf("Test 2 (Mixed case + punctuation)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 3 (Digits + spaces) ----------------
    {
        const char* plaintext = "CSCD 463 is fun";

        atbash_encrypt(plaintext, ciphertext);
        atbash_decrypt(ciphertext, decrypted);

        printf("Test 3 (Digits + spaces)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }
}