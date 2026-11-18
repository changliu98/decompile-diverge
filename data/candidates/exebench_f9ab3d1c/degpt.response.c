int str_to_int(char *input_string, int *result_value)
{
    int radix = 10; // Default radix is 10 (decimal)
    int index = 0;  // Index for iterating through the string
    *result_value = 0;   // Initialize the output number to 0

    // Check if the string starts with "0x" to indicate hexadecimal format
    if (input_string[0] == '0' && input_string[1] == 'x') {
        index = 2;  // Skip the "0x" prefix
        radix = 16; // Set radix to 16 (hexadecimal)
    }

    // If the string is empty or only contains the prefix, return an error
    if (input_string[index] == '\0') {
        return -1;
    }

    // Iterate through each character of the string until the null terminator
    for (; input_string[index] != '\0'; index++) {
        int current_digit; // Variable to store the numeric value of the current character

        // Handle decimal digits (0-9)
        if (input_string[index] >= '0' && input_string[index] <= '9') {
            current_digit = input_string[index] - '0';
        } else if (radix == 16) {
            // Handle hexadecimal digits (A-F, a-f) only if radix is 16
            if (input_string[index] >= 'A' && input_string[index] <= 'F') {
                current_digit = input_string[index] - 'A' + 10;
            } else if (input_string[index] >= 'a' && input_string[index] <= 'f') {
                current_digit = input_string[index] - 'a' + 10;
            } else {
                // Invalid character for the current radix
                return -1;
            }
        } else {
            // Invalid character for decimal radix
            return -1;
        }

        // Accumulate the number: multiply current value by radix and add the new digit
        *result_value = *result_value * radix + current_digit;
    }

    // Return success
    return 0;
}