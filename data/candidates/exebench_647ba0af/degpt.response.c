// Replaces all occurrences of 'find' with 'replace' in the string 'str'.
// Returns the modified string pointer.
char *replace_char(char *text, char target_char, char replacement_char)
{
    // Iterate through the string, finding each occurrence of 'find'
    // starting from the current position.
    for (char *found_index = strchr(text, target_char); found_index; found_index = strchr(found_index + 1, target_char)) {
        // Replace the found character with 'replace'
        *found_index = replacement_char;
    }
    // Return the original string pointer (modified in place)
    return text;
}