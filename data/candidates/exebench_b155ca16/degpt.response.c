/*
 * Appends a single character to the string pointed to by 't' and returns a pointer to the null terminator.
 *
 * Parameters:
 *   t - Pointer to the current end of the string (where the new character will be placed).
 *   c - The character to append.
 *
 * Returns:
 *   A pointer to the null terminator ('\0') following the appended character.
 */
char * object_desc_chr(char *dest, char ch)
{
    *dest = ch;       // Place the character at the current position
    dest[1] = '\0';  // Null-terminate the string immediately after the character
    return dest + 1; // Return pointer to the null terminator for chaining
}