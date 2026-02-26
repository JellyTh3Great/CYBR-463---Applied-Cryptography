/*
* Function declarations for Caesar cipher encryption and decryption.
*/

#ifndef CAESAR_H
#define CAESAR_H

// Encrypt plaintext using Caesar cipher with shift key (k)
void caesar_encrypt(const char* plaintext, char* ciphertext, int key);

// Decrypt ciphertext using Caesar cipher with shift key (k)
void caesar_decrypt(const char* ciphertext, char* plaintext, int key);

#endif