void string_reverse(char *str) {
    char *end = str;
    
    // Find the end of the string (null terminator)
    while (*end != '\0') {
        end++;
    }
    end--;
    
    // Reverse the string in place using XOR swap
    while ((size_t)str < (size_t)end) {
        *str ^= *end;
        *end ^= *str;
        *str ^= *end;
        
        str++;
        end--;
    }
}