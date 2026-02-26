/*
* Function declarations for Atbash cipher encryption and decryption.
* Encryption and decryption are identical for Atbash.
*/

#ifndef ATBASH_H
#define ATBASH_H

void atbash_encrypt(const char* plaintext, char* ciphertext);
void atbash_decrypt(const char* ciphertext, char* plaintext);

#endif