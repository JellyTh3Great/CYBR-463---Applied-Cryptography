/*
* Function declarations for Vigenere cipher encryption and decryption
*/

#ifndef VIGENERE_H
#define VIGENERE_H

void vigenere_encrypt(const char* plaintext, char* ciphertext, const char* key);
void vigenere_decrypt(const char* ciphertext, char* plaintext, const char* key);

#endif