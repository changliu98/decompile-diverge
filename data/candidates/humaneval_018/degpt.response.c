// Counts the number of non-overlapping occurrences of 'substring' in 'str'
int func0(char *text, char *pattern)
{
    int count = 0; // Initialize counter for occurrences
    size_t text_length = strlen(text); // Get length of the main string
    size_t pattern_length = strlen(pattern); // Get length of the substring
    // Iterate through the string, checking each position for a match
    for (size_t index = 0; index <= text_length - pattern_length; index++) {
        // Compare the substring starting at current position with the target substring
        if (strncmp(text + index, pattern, pattern_length) == 0) {
            count++; // Increment counter if a match is found
        }
    }
    return count; // Return the total count of occurrences
}