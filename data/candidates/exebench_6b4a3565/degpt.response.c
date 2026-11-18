char * my_strupcase(char *input_string)
{
    // Iterate through each character of the string until the null terminator
    for (int index = 0; input_string[index] != '\0'; index++) {
        // Check if the current character is a lowercase letter
        if (input_string[index] >= 'a' && input_string[index] <= 'z') {
            // Convert lowercase to uppercase by subtracting the ASCII difference (0x20)
            input_string[index] -= 0x20;
        }
    }
    // Return the pointer to the modified string
    return input_string;
}