void func0(char *input_string, char *output_string) {
    regex_t compiled_pattern;
    regmatch_t regex_matches[3];
    char copy_buffer[1024];

    // Compile the regex pattern to find a lowercase letter followed by an uppercase letter
    regcomp(&compiled_pattern, "([a-z])([A-Z])", 1);
    // Copy the input string to a buffer to allow modification during iteration
    strcpy(copy_buffer, input_string);
    // Initialize the result string as empty
    *output_string = '\0';
    // Pointer to track the current position in the buffer
    char *current_position = copy_buffer;
    // Loop while the regex matches at the current cursor position
    while (regexec(&compiled_pattern, current_position, 3, regex_matches, 0) == 0) {
        // Append the matched lowercase letter to the result
        strncat(output_string, current_position, regex_matches[1].rm_eo);
        // Add a space separator after the matched lowercase letter
        strcat(output_string, " ");
        // Move the cursor to the start of the matched uppercase letter
        current_position += regex_matches[2].rm_so;
    }
    // Append the remaining part of the string to the result
    strcat(output_string, current_position);
    // Free the compiled regex resources
    regfree(&compiled_pattern);
}