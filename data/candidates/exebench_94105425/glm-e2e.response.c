char* strrev(char* str) {
    char* start = str;
    char* end = str;

    // Find the end of the string (null terminator)
    while (end != NULL && *end != '\0') {
        end++;
    }
    
    // Step back one character to point to the last valid character
    end--;

    // Swap characters from the outside in
    while ((size_t)start < (size_t)end) {
        // XOR swap: *start ^= *end;
        *start = (char)(*start ^ *end);
        // XOR swap: *end ^= *start;
        *end = (char)(*end ^ *start);
        // XOR swap: *start ^= *end;
        *start = (char)(*start ^ *end);

        start++;
        end--;
    }

    return str;
}