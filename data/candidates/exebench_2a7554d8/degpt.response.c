int replace(char *input_string, char target_char, char replacement_char)
{
    // Iterate through the string 'rps' to find all occurrences of 'whatc'
    // Start by finding the first occurrence of 'whatc'
    for (char *current_position = strchr(input_string, target_char); current_position != NULL; current_position = strchr(current_position + 1, target_char)) {
        // Replace the found character 'whatc' with 'toc'
        *current_position = replacement_char;
    }
    // Return 0 to indicate successful completion
    return 0;
}