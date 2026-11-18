void reverse(char *str) {
    char *start = str;
    char *end = str;
    
    // Find the end of the string (pointing to the null terminator)
    while (*end != '\0') {
        end++;
    }
    
    // Step back twice to point to the last valid character
    // (Once for the null terminator, once to get the last char)
    end--;
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