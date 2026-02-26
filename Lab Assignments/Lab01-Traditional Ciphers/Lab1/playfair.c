/*
 * playfair.c
 *
 * Playfair Cipher (5x5, I/J combined)
 * ----------------------------------
 * Playfair encrypts PAIRS of letters (digraphs) using a 5x5 key square.
 * Because a 5x5 grid only holds 25 letters, Playfair traditionally combines I and J.
 *
 * Key square rules:
 * 1) Build a 5x5 grid using the keyword (remove duplicates).
 * 2) Fill the remaining letters of the alphabet (excluding J).
 *
 * Preprocessing plaintext:
 * - Keep letters only (omit spaces/punctuation/digits).
 * - Convert to uppercase.
 * - Replace J with I.
 * - Split into digraphs:
 *    - If a pair would be the same letter (e.g., "LL"), insert 'X' between them: "L X L"
 *    - If there's an odd number of letters, pad the last letter with 'X'
 *
 * Encryption rules (for each pair A B):
 * 1) Same row: replace each letter with the one to the RIGHT (wrap around).
 * 2) Same column: replace each letter with the one BELOW (wrap around).
 * 3) Rectangle: replace each letter with the one in the SAME ROW but in the OTHER letter's column.
 *
 * Decryption rules are the reverse:
 * - Same row: shift LEFT
 * - Same column: shift UP
 * - Rectangle: same rectangle swap rule (it reverses itself)
 *
 * Small example idea:
 *   If the two letters are in a rectangle:
 *      A . . B
 *      . . . .
 *      C . . D
 *   Then A becomes the letter in A's row and B's column, and B becomes the letter in B's row and A's column.
 *
 * Input behavior for this project:
 * - Letters only: non-letters are omitted (not preserved).
 * - Output letters are uppercase.
 * - Decryption performs a simple cleanup:
 *    - Remove trailing 'X' padding
 *    - Remove an 'X' that was inserted between duplicate letters (A X A -> A A)
 *
 * NOTE:
 * Cleanup can sometimes remove a real 'X' that was part of the original message,
 * but for this lab it is a standard and acceptable approach.
 */

#include "playfair.h"
#include "utils.h"

 /* 25-letter alphabet used to fill the square (J omitted because I/J are combined) */
static const char PF_ALPHA[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

/* ------------------------------------------------------------
   Helper: add a single character to the key square if not used
   ------------------------------------------------------------
   square: the 25-character array (row-major order)
   used  : tracks which letters have already been placed (A..Z)
   idx   : current insertion index (0..24)
*/
static void add_letter_to_square(char ch, char square[25], int used[26], int* idx)
{
    /* Playfair combines J with I */
    if (ch == 'J') ch = 'I';

    /* Convert 'A'..'Z' -> 0..25 */
    int v = char_to_int(ch);
    if (v < 0 || v > 25) return;

    /* If not used yet, add it to the square */
    if (!used[v]) {
        used[v] = 1;
        if (*idx < 25) {
            square[*idx] = ch;
            (*idx)++;
        }
    }
}

/* ------------------------------------------------------------
   Build the 5x5 key square + position lookup table
   ------------------------------------------------------------
   square: 25 letters, row-major: square[row*5 + col]
   pos   : maps A..Z -> index 0..24, with J mapped to I's position
*/
static void build_square(const char* key, char square[25], int pos[26])
{
    int used[26] = { 0 };
    int idx = 0;

    /* Initialize all positions to "not found" */
    for (int i = 0; i < 26; i++) {
        pos[i] = -1;
    }

    /* 1) Add keyword letters first (letters only, uppercase, J->I, no duplicates) */
    for (int i = 0; key[i] != '\0'; i++) {
        if (is_alpha(key[i])) {
            char ch = to_upper(key[i]);
            if (ch == 'J') ch = 'I';
            add_letter_to_square(ch, square, used, &idx);
        }
    }

    /* 2) Fill the rest of the square with remaining letters (A..Z without J) */
    for (int i = 0; PF_ALPHA[i] != '\0'; i++) {
        add_letter_to_square(PF_ALPHA[i], square, used, &idx);
    }

    /* 3) Build lookup table from letter -> index in square */
    for (int i = 0; i < 25; i++) {
        int v = char_to_int(square[i]);
        pos[v] = i;
    }

    /* Ensure J maps to the same place as I */
    pos[char_to_int('J')] = pos[char_to_int('I')];
}

/* ------------------------------------------------------------
   Extract letters only, uppercase, and map J -> I
   ------------------------------------------------------------
   Returns number of letters copied.
*/
static int extract_letters(const char* in, char* out, int max_out)
{
    int n = 0;

    for (int i = 0; in[i] != '\0' && n < max_out - 1; i++) {
        if (is_alpha(in[i])) {
            char ch = to_upper(in[i]);
            if (ch == 'J') ch = 'I';
            out[n++] = ch;
        }
    }

    out[n] = '\0';
    return n;
}

/* ------------------------------------------------------------
   Turn a stream of letters into Playfair digraph text
   ------------------------------------------------------------
   - Insert 'X' between duplicate letters in the same pair: "LL" -> "L X L ..."
   - Pad with 'X' if the total length is odd.
   Returns prepared length (always even).
*/
static int prepare_digraphs(const char* letters, char* prepared, int max_prepared)
{
    int i = 0; /* index into letters[] */
    int p = 0; /* index into prepared[] */

    while (letters[i] != '\0' && p < max_prepared - 2) {
        char a = letters[i++];
        char b = letters[i]; /* look-ahead */

        if (b == '\0') {
            /* One letter left: pad with X to make a pair */
            prepared[p++] = a;
            prepared[p++] = 'X';
            break;
        }

        if (a == b) {
            /* Duplicate pair: insert X and do NOT consume b yet */
            prepared[p++] = a;
            prepared[p++] = 'X';
        }
        else {
            /* Normal pair: consume b */
            prepared[p++] = a;
            prepared[p++] = b;
            i++;
        }
    }

    prepared[p] = '\0';
    return p;
}

/* ------------------------------------------------------------
   Encrypt/decrypt a single digraph using the key square
   ------------------------------------------------------------
   decrypt = 0 -> encrypt
   decrypt = 1 -> decrypt
*/
static void transform_pair(char a, char b,
    char* out1, char* out2,
    const char square[25], const int pos[26],
    int decrypt)
{
    /* Find each letter in the square (0..24) */
    int ia = pos[char_to_int(a)];
    int ib = pos[char_to_int(b)];

    /* Convert flat index to (row, col) */
    int ra = ia / 5, ca = ia % 5;
    int rb = ib / 5, cb = ib % 5;

    if (ra == rb) {
        /* Same row:
           - encrypt: shift RIGHT
           - decrypt: shift LEFT */
        if (!decrypt) {
            ca = (ca + 1) % 5;
            cb = (cb + 1) % 5;
        }
        else {
            ca = (ca + 4) % 5; /* -1 mod 5 */
            cb = (cb + 4) % 5;
        }

        *out1 = square[ra * 5 + ca];
        *out2 = square[rb * 5 + cb];
    }
    else if (ca == cb) {
        /* Same column:
           - encrypt: shift DOWN
           - decrypt: shift UP */
        if (!decrypt) {
            ra = (ra + 1) % 5;
            rb = (rb + 1) % 5;
        }
        else {
            ra = (ra + 4) % 5; /* -1 mod 5 */
            rb = (rb + 4) % 5;
        }

        *out1 = square[ra * 5 + ca];
        *out2 = square[rb * 5 + cb];
    }
    else {
        /* Rectangle rule:
           Swap columns (keep each letter's row, take the other letter's column) */
        *out1 = square[ra * 5 + cb];
        *out2 = square[rb * 5 + ca];
    }
}

/* ------------------------------------------------------------
   Cleanup decrypted text (optional Playfair convenience)
   ------------------------------------------------------------
   1) Remove trailing 'X' (common padding)
   2) Remove 'X' that was inserted between duplicates: A X A -> A A
*/
static void cleanup_decrypted(char* text)
{
    int len = 0;
    while (text[len] != '\0') len++;

    /* Remove trailing padding X */
    if (len > 0 && text[len - 1] == 'X') {
        text[len - 1] = '\0';
        len--;
    }

    /* Remove filler X in the pattern A X A */
    char cleaned[512];
    int c = 0;

    for (int i = 0; i < len; i++) {
        if (i > 0 && i < len - 1 &&
            text[i] == 'X' &&
            text[i - 1] == text[i + 1]) {
            /* Skip filler X */
            continue;
        }
        cleaned[c++] = text[i];
    }

    cleaned[c] = '\0';

    /* Copy cleaned text back */
    int i = 0;
    while (cleaned[i] != '\0') {
        text[i] = cleaned[i];
        i++;
    }
    text[i] = '\0';
}

/* ------------------------------------------------------------
   Public API: Encrypt
   ------------------------------------------------------------ */
void playfair_encrypt(const char* plaintext, char* ciphertext, const char* key)
{
    char square[25];
    int pos[26];

    char letters[512];
    char prepared[512];

    /* Build key square + lookup table */
    build_square(key, square, pos);

    /* Step 1: sanitize plaintext into letters-only form */
    extract_letters(plaintext, letters, (int)sizeof(letters));

    /* Step 2: build digraph stream (duplicate handling + padding) */
    int plen = prepare_digraphs(letters, prepared, (int)sizeof(prepared));

    /* Step 3: encrypt each pair */
    int out = 0;
    for (int i = 0; i < plen; i += 2) {
        char o1, o2;
        transform_pair(prepared[i], prepared[i + 1], &o1, &o2, square, pos, 0);
        ciphertext[out++] = o1;
        ciphertext[out++] = o2;
    }

    ciphertext[out] = '\0';
}

/* ------------------------------------------------------------
   Public API: Decrypt
   ------------------------------------------------------------ */
void playfair_decrypt(const char* ciphertext, char* plaintext, const char* key)
{
    char square[25];
    int pos[26];
    char letters[512];

    /* Build key square + lookup table */
    build_square(key, square, pos);

    /* Sanitize ciphertext to letters-only */
    int n = extract_letters(ciphertext, letters, (int)sizeof(letters));

    /* If odd length, it cannot be valid digraph input; copy safely */
    if (n % 2 != 0) {
        int i = 0;
        while (letters[i] != '\0') {
            plaintext[i] = letters[i];
            i++;
        }
        plaintext[i] = '\0';
        return;
    }

    /* Decrypt each pair */
    int out = 0;
    for (int i = 0; i < n; i += 2) {
        char o1, o2;
        transform_pair(letters[i], letters[i + 1], &o1, &o2, square, pos, 1);
        plaintext[out++] = o1;
        plaintext[out++] = o2;
    }

    plaintext[out] = '\0';

    /* Optional cleanup for padding/filler */
    cleanup_decrypted(plaintext);
}
