/*
* Contains Caesar cipher test cases required by the lab.
* Prints plaintext, key, expected (when applicable), actual ciphertext,
* and decrypted plaintext.
*/

#include <stdio.h>
#include "test_caesar.h"
#include "caesar.h"

void run_caesar_tests(void) {
	char ciphertext[256];
	char decrypted[256];

	printf("========================================\n");
	printf(" Caesar Cipher - Test Cases\n");
	printf("========================================\n\n");

    // ---------------- Test 1 (Lab example) ----------------
    {
        const char* plaintext = "HELLO";
        int key = 3;
        const char* expected = "KHOOR";

        caesar_encrypt(plaintext, ciphertext, key);
        caesar_decrypt(ciphertext, decrypted, key);

        printf("Test 1 (Lab Example)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %d\n", key);
        printf("Expected  : %s\n", expected);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 2 (Mixed case + punctuation) ----------------
    {
        const char* plaintext = "Hello, World!";
        int key = 5;

        caesar_encrypt(plaintext, ciphertext, key);
        caesar_decrypt(ciphertext, decrypted, key);

        printf("Test 2 (Mixed case + punctuation)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %d\n", key);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 3 (Digits + spaces) ----------------
    {
        const char* plaintext = "CSCD 463 is fun";
        int key = 1;

        caesar_encrypt(plaintext, ciphertext, key);
        caesar_decrypt(ciphertext, decrypted, key);

        printf("Test 3 (Digits + spaces)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %d\n", key);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }
}