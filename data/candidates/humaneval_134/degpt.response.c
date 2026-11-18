int func0(char *input_string)
{
    // Calculate the length of the input string
    size_t string_length = strlen(input_string);
    // If the string is empty, return 0
    if (string_length == 0) return 0;
    
    // Get the last character of the string, cast to unsigned char to avoid sign extension issues
    unsigned char final_character = (unsigned char)input_string[string_length - 1];
    // Check if the last character is a letter using the ctype library's _ISalpha flag (0x400)
    // If the last character is not a letter, return 0
    if (!((*__ctype_b_loc())[final_character] & 0x400)) return 0;
    
    // If the string has only one character and it is a letter, return 1
    if (string_length == 1) return 1;
    
    // Get the second-to-last character of the string, cast to unsigned char
    unsigned char penultimate_character = (unsigned char)input_string[string_length - 2];
    // Check if the second-to-last character is a letter
    // If the second-to-last character is a letter, return 0; otherwise, return 1
    return ((*__ctype_b_loc())[penultimate_character] & 0x400) ? 0 : 1;
}