// Truncates the input string at the first occurrence of the specified character.
// If the character is found, it is replaced with a null terminator, effectively
// shortening the string. If the character is not found, the string remains unchanged.
// Returns the original string pointer.
char *truncate_string_at_char(char *input_string, char delimiter)
{
    // Iterate through each character of the string until the null terminator is reached
    for (char *current_char_ptr = input_string; *current_char_ptr != '\0'; current_char_ptr++) {
        // Check if the current character matches the target character
        if (*current_char_ptr == delimiter) {
            // Replace the matching character with a null terminator to truncate the string
            *current_char_ptr = '\0';
            // Exit the loop after truncation
            break;
        }
    }
    // Return the modified string pointer
    return input_string;
}