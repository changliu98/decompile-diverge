char * convert_set_base(char *input_string, int *output_base)
{
    // Initialize the base to decimal (10) by default
    *output_base = 10;
    
    // Check if the string is valid and starts with "0x" or "0X"
    if (input_string && *input_string == '0' && (input_string[1] == 'x' || input_string[1] == 'X')) {
        // Set the base to hexadecimal (16)
        *output_base = 0x10;
        // Return a pointer to the character after "0x" or "0X"
        return input_string + 2;
    }
    
    // Return the original string pointer if no hex prefix is found
    return input_string;
}