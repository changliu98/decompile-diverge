char *ft_strupcase(char *input_string)
{
    // Iterate through the string until the null terminator is reached
    for (int index = 0; input_string[index] != '\0'; index++)
        // Check if the current character is a lowercase letter
        if (input_string[index] >= 'a' && input_string[index] <= 'z')
            // Convert the lowercase letter to uppercase by subtracting 0x20 (32)
            input_string[index] -= 0x20;
    // Return the modified string
    return input_string;
}