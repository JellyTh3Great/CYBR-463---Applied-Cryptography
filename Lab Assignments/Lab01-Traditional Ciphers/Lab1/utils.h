/*
Function declaration for shared utility helpers used by all cipher files.
*/
#ifndef UTILS_H
#define UTILS_H

// Converts an uppercase character to a number 0-25
int char_to_int(char c);

// Converts a number 0-25 back to an uppercase character
char int_to_char(int i);

// Returns 1 is the character is alphabetic, 0 otherwise
int is_alpha(char c);

// Converts lowercase letters to uppercase
char to_upper(char c);

#endif
