# Lab 02 – Introduction to Modern Symmetric Ciphers  
**CYBR 463 – Applied Cryptography**

## Overview
This project implements foundational **bit-level building blocks** used in modern symmetric cryptography, following the requirements of **Lab 02**.

Rather than full encryption algorithms, this lab focuses on the *low-level operations* that real block ciphers rely on internally, such as splitting words, swapping halves, rotating bits, and applying permutation boxes (P-boxes).

Each task:
- Is implemented in **C**
- Can be run interactively with custom input
- Includes test cases demonstrating the examples from the lab PDF (including the corrected example provided by the instructor)

The emphasis of this lab is correctness, clarity, and understanding how modern symmetric ciphers manipulate data at the bit level.

---

## Implemented Tasks

### 1. Split Word
- Splits an `n`-bit word into two equal halves
- Left half contains the most significant bits
- Right half contains the least significant bits
- Used as a foundational step in Feistel-style designs

---

### 2. Combine Halves
- Combines two equal-sized halves into a single `n`-bit word
- Inverse operation of **Split Word**
- Demonstrates controlled bit composition

---

### 3. Swap Halves
- Swaps the left and right halves of an `n`-bit word
- Implemented by reusing:
  - `split_word`
  - `combine_halves`
- Models the half-swapping step common in block ciphers

---

### 4. Bit Rotation
- Supports left and right circular rotations
- Wraps bits that “fall off” one side back onto the other
- Rotation is constrained to a specified number of bits
- Used heavily in modern cipher diffusion layers

---

### 5. P-box Permutation
- Implements a permutation box (P-box)
- Rearranges bits according to a permutation table
- Uses the convention:
  - Bits numbered `1..n` from MSB → LSB
- Includes the **corrected example** provided by the instructor

---

### 6. Invert Permutation
- Computes the inverse of a permutation table
- Applying a permutation followed by its inverse restores the original order
- Demonstrates reversibility, a key property in cryptographic design

---

## Program Structure

### Menu System
The program follows the same menu-driven structure used in **Lab 01**:

1. **Main Menu** – select a task  
2. **Submenu** – choose to:
   - Run the function with custom user input
   - Run predefined test cases (from the lab PDF)

This allows both verification and hands-on experimentation.

---

## Running the Program

### Build
- Open the solution in **Visual Studio Community**
- Build the project (`Build → Build Solution`)

### Run
- Start the program (`Debug → Start Without Debugging`)
- Use the menus to select a task and execution mode

---

## Test Cases
Each task includes a dedicated test file:
- Test cases include:
  - The example(s) shown in the lab PDF
  - Additional edge and sanity checks
- Output displays:
  - Decimal values
  - Binary representations
- Binary output is printed explicitly to aid visualization and understanding

---

## Design Notes
- No cryptographic libraries are used
- All bit manipulation is implemented manually using shifts and masks
- Input handling uses `fgets` and `strtol` for safety and consistency
- Code is modularized into:
  - One source/header pair per task
  - Shared helper functions in `utils.c`
  - Separate test files per task
- The menu structure is intentionally consistent with Lab 01 for continuity

---

## Citations
- OpenAI. *ChatGPT, GPT-5.2*, 2025, https://chat.openai.com/  
  - Portions of this project were developed with the assistance of ChatGPT (GPT-5.2), a large language model by OpenAI, used for conceptual clarification, debugging guidance, and code review.  
  - All final implementations were written, tested, and verified by the author.

---

## Author
Joel Sivanish  
CYBR 463 – Applied Cryptography
