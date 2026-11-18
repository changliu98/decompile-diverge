int func0(char *inputString)
{
    int charValueSum = 0;
    // Iterate through each character of the string until the null terminator
    for (int index = 0; inputString[index] != '\0'; index++) {
        // Add the character's value minus 0x60 (96) to the sum
        // This effectively converts lowercase letters 'a'-'z' to 1-26
        charValueSum += inputString[index] - 0x60;
    }
    // If the sum modulo 0x1a (26) is 0, return 0x7a (122, 'z')
    // Otherwise, return the remainder modulo 26 plus 0x60 (96)
    return charValueSum % 0x1a == 0 ? 0x7a : charValueSum % 0x1a + 0x60;
}