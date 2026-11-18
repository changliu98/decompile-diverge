int func0(char *s)
{
    int vowelCount = 0; // Initialize vowel counter
    int strLen = strlen(s); // Get string length
    for (int idx = 0; idx < strLen; idx++) {
        char currentChar = s[idx]; // Get current character
        // Check if character is a standard vowel (both lowercase and uppercase)
        if (currentChar == 'a' || currentChar == 'e' || currentChar == 'i' || currentChar == 'o' || currentChar == 'u' ||
            currentChar == 'A' || currentChar == 'E' || currentChar == 'I' || currentChar == 'O' || currentChar == 'U') {
            vowelCount++; // Increment counter for standard vowels
        }
    }
    // Check if string ends with 'y' or 'Y' and is not empty
    if (strLen > 0 && (s[strLen - 1] == 'y' || s[strLen - 1] == 'Y')) {
        vowelCount++; // Increment counter for trailing 'y'
    }
    return vowelCount; // Return total count of vowels including trailing 'y'
}