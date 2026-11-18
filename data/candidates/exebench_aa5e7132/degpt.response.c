void GetWord(char *output_buffer, char *input_string, int max_length) {
    // Skip leading non-printable characters (ASCII < '!') until end of string
    while (*input_string < '!' && *input_string != '\0') input_string++;
    
    int char_count = 0;
    // Copy characters that are printable (ASCII > ' ') and not null terminator,
    // up to max - 1 characters to leave room for the null terminator
    while (*input_string > ' ' && *input_string != '\0' && char_count < max_length - 1) {
        *output_buffer++ = *input_string++;
        char_count++;
    }
    // Null-terminate the output string
    *output_buffer = '\0';
}