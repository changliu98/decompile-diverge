int func0(char *inputString, char targetChar) {
    int index;
    // Iterate through the string until the null terminator is reached
    for (index = 0; inputString[index] != '\0'; index++) {
        // Check if the current character matches the target character
        if (inputString[index] == targetChar) {
            // Return the 1-based index of the first occurrence
            return index + 1;
        }
    }
    // Return -1 if the character is not found
    return -1;
}