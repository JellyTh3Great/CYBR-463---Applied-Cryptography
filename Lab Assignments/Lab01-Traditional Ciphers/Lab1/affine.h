/*
* Function ceclarations for the affine cipher.
*/

#ifndef AFFINE_H
#define AFFINE_H

void affine_encrypt(const char* plaintext, char* ciphertext, int a, int b);
void affine_decrypt(const char* ciphertext, char* plaintext, int a, int b);

#endif#pragma once
