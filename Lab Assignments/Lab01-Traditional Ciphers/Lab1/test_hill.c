#include <stdio.h>
#include "test_hill.h"
#include "hill.h"

void run_hill_tests(void)
{
    char ciphertext[512];
    char decrypted[512];

    printf("========================================\n");
    printf(" Hill Cipher (2x2) - Test Cases\n");
    printf("========================================\n\n");

    // ---------------- Test 1 (Lab PDF example) ----------------
    {
        const char* plaintext = "HELP";
        int K[2][2] = { {1, 8}, {8, 5} };
        const char* expected = "NYBH"; // From lab PDF:contentReference[oaicite:2]{index=2}

        hill_encrypt_2x2(plaintext, ciphertext, K);
        hill_decrypt_2x2(ciphertext, decrypted, K);

        printf("Test 1 (Lab Example)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("K         : [[%d,%d],[%d,%d]]\n", K[0][0], K[0][1], K[1][0], K[1][1]);
        printf("Expected  : %s\n", expected);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 2 (Mixed case + punctuation) ----------------
    {
        const char* plaintext = "He!lp?";
        int K[2][2] = { {1, 8}, {8, 5} };

        hill_encrypt_2x2(plaintext, ciphertext, K);
        hill_decrypt_2x2(ciphertext, decrypted, K);

        printf("Test 2 (Mixed case + punctuation)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("K         : [[%d,%d],[%d,%d]]\n", K[0][0], K[0][1], K[1][0], K[1][1]);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
    }

    // ---------------- Test 3 (Digits + spaces) ----------------
    {
        const char* plaintext = "CSCD 463 is fun";
        int K[2][2] = { {3, 3}, {2, 5} }; // common invertible 2x2 key

        hill_encrypt_2x2(plaintext, ciphertext, K);
        hill_decrypt_2x2(ciphertext, decrypted, K);

        printf("Test 3 (Digits + spaces)\n");
        printf("Plaintext : %s\n", plaintext);
        printf("K         : [[%d,%d],[%d,%d]]\n", K[0][0], K[0][1], K[1][0], K[1][1]);
        printf("Encrypted : %s\n", ciphertext);
        printf("Decrypted : %s\n\n", decrypted);
        printf("Note      : Hill (like Playfair here) strips non-letters.\n\n");
    }
}
