char * my_strupcase(char *str)
{
    // Check if the input string pointer is NULL
    if (str == NULL) {
        return NULL;
    }
    // Iterate through each character of the string until the null terminator
    for (int index = 0; str[index] != '\0'; index++) {
        // Check if the character is a lowercase letter (ASCII range 'a' to 'z')
        // '`' is ASCII 96, '{' is ASCII 123; lowercase letters are between 97 and 122
        if (str[index] > '`' && str[index] < '{') {
            // Convert lowercase to uppercase by subtracting 0x20 (32 in decimal)
            str[index] -= 0x20;
        }
    }
    // Return the modified string pointer
    return str;
}