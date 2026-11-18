/*
 * Skips characters in the string 's' until the character 'c' is found.
 * Modifies the string by null-terminating it at the position of 'c',
 * then advances the pointer past 'c'.
 *
 * Parameters:
 *   s - pointer to the string to process
 *   c - the character to skip until
 *
 * Returns:
 *   pointer to the character after 'c', or NULL if 'c' is not found
 */
char * skip(char *str, char target_char)
{
    // Advance pointer until end of string or character 'c' is found
    while (*str != '\0' && *str != target_char) {
        str++;
    }
    // If character 'c' was found, null-terminate the string and advance past 'c'
    if (*str != '\0') {
        *str = '\0';
        str++;
    }
    // Return pointer to the character after 'c' (or NULL if not found)
    return str;
}