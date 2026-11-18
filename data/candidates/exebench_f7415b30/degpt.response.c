// Converts a multibyte character to a wide character.
// Returns the number of bytes consumed from the multibyte string,
// or 0 if the input is empty or null-terminated.
int dummywc_mbtowc(int *output_char, char *input_string, size_t string_length)
{
    // If no bytes are available or the string is empty, return 0.
    if ((string_length == 0) || (*input_string == '\0')) {
        return 0;
    }
    // Convert the single-byte character to a wide character.
    *output_char = (int)*input_string;
    // Return 1 to indicate one byte was consumed.
    return 1;
}