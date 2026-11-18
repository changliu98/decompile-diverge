void decrypt(char *text, int key)
{
    int index;
    // Iterate through each character of the string until the null terminator
    for (index = 0; text[index] != '\0'; index = index + 1) {
        // Replace hyphen characters with spaces
        if (text[index] == '-') {
            text[index] = ' ';
        }
        else {
            // Decrypt alphabetic characters using a Caesar cipher with a shift
            // Maps 'a'-'z' (0-25) to the shifted position within the 26-letter alphabet
            text[index] = (char)((text[index] + -0x61 + key % 0x1a) % 0x1a) + 'a';
        }
    }
}