int func0(char *input_string)
{
    int max_whitespace_length = 0;          // Result: maximum length of consecutive whitespace found
    int current_whitespace_length = 0;          // Counter: current length of consecutive whitespace
    size_t string_length = strlen(input_string); // Length of the input string
    ushort **ctype_b_table = __ctype_b_loc(); // Pointer to locale-specific character classification table

    for (int character_index = 0; character_index < (int)string_length; character_index++) {
        // Check if current character is whitespace using the ctype_b table
        // The 0x100 bit in __ctype_b indicates whitespace
        if ((ctype_b_table[(int)input_string[character_index]] & 0x100) == 0) {
            // Current character is not whitespace
            // Update result if the current run of whitespace is longer than previous maximum
            if (max_whitespace_length < current_whitespace_length) {
                max_whitespace_length = current_whitespace_length;
            }
            // Reset counter for the next potential whitespace sequence
            current_whitespace_length = 0;
        } else {
            // Current character is whitespace, increment the counter
            current_whitespace_length++;
        }
    }

    // After the loop, check if the string ended with whitespace
    // If so, compare the final count with the result
    if ((ctype_b_table[(int)input_string[string_length - 1]] & 0x100) != 0 && max_whitespace_length < current_whitespace_length) {
        max_whitespace_length = current_whitespace_length;
    }

    return max_whitespace_length;
}