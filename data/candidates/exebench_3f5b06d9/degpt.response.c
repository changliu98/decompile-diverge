/*
 * Converts the input string to uppercase in-place.
 *
 * @param str Pointer to the null-terminated string to convert.
 * @return The same pointer passed as 'str'.
 */
char * my_strupcase(char *str)
{
    // Iterate through each character of the string until the null terminator
    for (int index = 0; str[index] != '\0'; index++) {
        // Check if the current character is a lowercase letter
        if (str[index] >= 'a' && str[index] <= 'z') {
            // Convert lowercase to uppercase by subtracting the ASCII difference (0x20)
            str[index] -= 0x20;
        }
    }
    // Return the modified string pointer
    return str;
}