void reverse(char *str) {
    char *end = str;
    char *start = str;

    // Find the null terminator
    while (*end != '\0') {
        end++;
    }
    
    // Point to the last character before the null terminator
    end--;

    // Swap characters from the outside in
    while (start < end) {
        // XOR swap algorithm
        *start ^= *end;
        *end ^= *start;
        *start ^= *end;

        start++;
        end--;
    }
}