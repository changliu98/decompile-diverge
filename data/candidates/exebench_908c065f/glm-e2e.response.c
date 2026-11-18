void reverse(char *str) {
    char *start = str;
    char *end = str;
    char temp;

    // Find the end of the string (null terminator)
    while (*end != '\0') {
        end++;
    }
    
    // Step back one character to the last valid character
    end--;

    // Swap characters from the outside in
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}