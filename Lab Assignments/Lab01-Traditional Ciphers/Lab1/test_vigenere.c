/*
 * Test cases for the Vigenere cipher.
 * This file ONLY contains test code.
 */

#include <stdio.h>
#include "test_vigenere.h"
#include "vigenere.h"

void run_vigenere_tests(void)
{
    char ciphertext[256];
    char decrypted[256];

    printf("========================================\n");
    printf(" Vigenere Cipher - Test Cases\n");
    printf("========================================\n\n");

    // ---------------- Test 1 (Classic example) ----------------
    {
        const char* plaintext = "ATTACKATDAWN";
        const char* key = "LEMON";
        const char* expected = "LXFOPVEFRNHR";

        vigenere_encrypt(plaintext, ciphertext, key);
        vigenere_decrypt(ciphertext, decrypted, key);

        printf("Test 1 (Classic)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %s\n", key);
        printf("Expected  : %s\n", expected);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 2 (Mixed case + punctuation) ----------------
    {
        const char* plaintext = "Hello, World!";
        const char* key = "KEY";

        vigenere_encrypt(plaintext, ciphertext, key);
        vigenere_decrypt(ciphertext, decrypted, key);

        printf("Test 2 (Mixed case + punctuation)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %s\n", key);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 3 (Digits + spaces) ----------------
    {
        const char* plaintext = "CSCD 463 is fun";
        const char* key = "ABC";  // shifts: 0,1,2 repeating

        vigenere_encrypt(plaintext, ciphertext, key);
        vigenere_decrypt(ciphertext, decrypted, key);

        printf("Test 3 (Digits + spaces)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %s\n", key);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }
}
