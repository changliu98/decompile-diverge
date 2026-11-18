char * stb_skipnewline(char *input_string)
{
    // If the current character is a carriage return or newline, advance the pointer
    if ((*input_string == '\r') || (*input_string == '\n')) {
        input_string++;
    }
    // Return the (possibly incremented) pointer
    return input_string;
}