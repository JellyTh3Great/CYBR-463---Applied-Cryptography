/*
 * playfair.h
 *
 * Function declarations for the Playfair cipher.
 */

#ifndef PLAYFAIR_H
#define PLAYFAIR_H

void playfair_encrypt(const char* plaintext, char* ciphertext, const char* key);
void playfair_decrypt(const char* ciphertext, char* plaintext, const char* key);

#endif
