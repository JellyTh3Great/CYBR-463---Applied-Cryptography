# Lab 01 – Traditional Ciphers  
**CYBR 463 – Applied Cryptography**

## Overview
This project implements several classical cryptographic ciphers in **C**, following the requirements of Lab 01.  
Each cipher supports encryption and decryption, includes automated test cases, and can also be run interactively through a menu-driven program.

The focus of this lab is correctness, clarity, and understanding of how classical ciphers work internally.

---

## Implemented Ciphers

### 1. Caesar Cipher
- Shift-based substitution cipher
- Supports arbitrary integer shifts
- Preserves non-letter characters

### 2. Atbash Cipher
- Fixed substitution cipher (A ↔ Z, B ↔ Y, etc.)
- Encryption and decryption are the same operation
- Preserves non-letter characters

### 3. Vigenère Cipher
- Polyalphabetic substitution cipher
- Uses a keyword to determine shifts
- Preserves non-letter characters

### 4. Affine Cipher
- Mathematical substitution cipher:  
  \[
  E(x) = (ax + b) \bmod 26
  \]
- Requires `a` to be invertible modulo 26
- Preserves non-letter characters

### 5. Playfair Cipher (5×5)
- Classic Playfair cipher with I/J combined
- Uses digraphs (pairs of letters)
- Inserts filler `X` for duplicate letters and padding
- **Letters only**: non-letter characters are omitted
- Decryption removes common padding and filler `X`

### 6. Hill Cipher (2×2)
- Matrix-based cipher:
  \[
  C = KP \bmod 26
  \]
- Uses a 2×2 invertible key matrix
- Pads with `X` if needed
- **Letters only**: non-letter characters are omitted
- Decryption uses the modular inverse of the key matrix

---

## Program Structure

### Menu System
When the program runs, it presents:

1. **Main Menu** – select a cipher  
2. **Submenu** – choose to:
   - Run the cipher interactively (encrypt/decrypt)
   - Run automated test cases

This allows both verification and manual experimentation.

---

## Running the Program

### Build
- Open the solution in **Visual Studio Community**
- Build the project (`Build → Build Solution`)

### Run
- Start the program (`Debug → Start Without Debugging`)
- Use the menus to select a cipher and operation

---

## Test Cases
Each cipher includes a dedicated test file:
- Tests include:
  - Simple examples
  - Mixed case and punctuation
  - Digits and spaces (when applicable)
- Output uses consistent labels:
  - `Plaintext`
  - `Encrypted`
  - `Decrypted`
  - `Expected` (when a known reference value exists)

For Playfair and Hill, tests demonstrate that non-letter characters are omitted, consistent with their classic definitions.

---

## Design Notes
- No helper libraries like `<ctype.h>` are used; all character handling is implemented manually.
- Input handling uses `fgets` and `strtol` for safety and portability.
- Code is modularized into:
  - One source/header pair per cipher
  - Separate test files
- Only one `main()` function is used; test files expose `run_*_tests()` functions.

## Citations:
- OpenAI. ChatGPT, GPT-5.2, 2025, https://chat.openai.com/
	-Portions of this project were developed with the assistance of ChatGPT (GPT-5.2), a large language model by OpenAI, used for conceptual clarification, debugging guidance, 
	 and code review. All final implementations were written, tested, and verified by the author.

---

## Author
Joel Sivanish  
CYBR 463 – Applied Cryptography
