#include <stdio.h>
#include "test_playfair.h"
#include "playfair.h"

void run_playfair_tests(void)
{
    char ciphertext[512];
    char decrypted[512];

    printf("========================================\n");
    printf(" Playfair Cipher - Test Cases\n");
    printf("========================================\n\n");

    // Test 1 (Key from lab example)
    {
        const char* plaintext = "HELLO";
        const char* key = "MONARCHY";
        /* Standard Playfair result for HELLO with MONARCHY is CFSUPM
           because HELLO -> HE LX LO (inserts X between double L). */
        const char* expected = "CFSUPM";

        playfair_encrypt(plaintext, ciphertext, key);
        playfair_decrypt(ciphertext, decrypted, key);

        printf("Test 1 (Lab Key)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %s\n", key);
        printf("Expected  : %s\n", expected);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    /* Test 2 (Mixed case + punctuation)
       Note: this implementation strips non-letters by design. */
    {
        const char* plaintext = "Hello, World!";
        const char* key = "MONARCHY";

        playfair_encrypt(plaintext, ciphertext, key);
        playfair_decrypt(ciphertext, decrypted, key);

        printf("Test 2 (Mixed case + punctuation)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %s\n", key);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 3 (Digits + spaces) ----------------
    {
        const char* plaintext = "CSCD 463 is fun";
        const char* key = "MONARCHY";

        playfair_encrypt(plaintext, ciphertext, key);
        playfair_decrypt(ciphertext, decrypted, key);

        printf("Test 3 (Digits + spaces)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("Key       : %s\n", key);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);

        // Note: Playfair strips non-letters, so decrypted will be "CSCDISFUN"
    }

}
