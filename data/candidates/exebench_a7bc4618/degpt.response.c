// Removes the specified line ending character from the end of the string.
// If the character is found, it is replaced with a null terminator.
void remove_line_ending(char *input_string, char line_ending_char)
{
    // Find the last occurrence of the specified ending character in the string.
    char *last_ending_pos = strrchr(input_string, line_ending_char);
    // If the ending character was found, replace it with a null terminator to truncate the string.
    if (last_ending_pos != NULL) {
        *last_ending_pos = '\0';
    }
}