void tosuper(char *inputString)
{
    // Iterate through the string until the null terminator is reached
    for (int index = 0; inputString[index] != '\0'; index++) {
        // Check if the character is a lowercase letter (ASCII range 'a' to 'z')
        // '`' is 0x60 and '{' is 0x7B; lowercase letters are between 0x61 and 0x7A
        if (inputString[index] > '`' && inputString[index] < '{') {
            // Convert lowercase to uppercase by subtracting 0x20 (32)
            inputString[index] -= 0x20;
        }
    }
}