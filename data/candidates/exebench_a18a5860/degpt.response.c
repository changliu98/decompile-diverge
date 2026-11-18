/**
 * Clears the given string and resets its length to zero.
 *
 * @param s  Pointer to the string buffer to be cleared.
 * @param len Pointer to the variable holding the current length of the string.
 */
void jsonny_clear(char *buffer, size_t *length)
{
    // Reset the length to zero
    *length = 0;
    // Null-terminate the string to effectively clear it
    *buffer = '\0';
}