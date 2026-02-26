/*
 * Function declarations for the Hill cipher (2x2 matrix).
 */

#ifndef HILL_H
#define HILL_H

 // Encrypt using a 2x2 key matrix K.
void hill_encrypt_2x2(const char* plaintext, char* ciphertext, int K[2][2]);

// Decrypt using a 2x2 key matrix K (computes K^-1 mod 26).
void hill_decrypt_2x2(const char* ciphertext, char* plaintext, int K[2][2]);

#endif
