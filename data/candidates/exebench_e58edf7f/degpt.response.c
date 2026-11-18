void toUpperCase(char *text)
{
    // Iterate through each character of the string until the null terminator
    for (int index = 0; text[index] != '\0'; index++) {
        // Check if the current character is a lowercase letter
        if (text[index] >= 'a' && text[index] <= 'z') {
            // Convert to uppercase by subtracting the ASCII difference between lowercase and uppercase letters
            text[index] -= 0x20;
        }
    }
}