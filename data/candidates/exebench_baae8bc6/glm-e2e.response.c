void reverse(char *str) {
    char *end = str;
    
    // Find the end of the string (null terminator)
    while (*end != '\0') {
        end++;
    }
    
    // Step back one character to the last valid character
    end--;
    
    // Swap characters from the outside in
    while (str < end) {
        // XOR swap implemented via addition and subtraction
        *str = *str - *end;
        *end = *end + *str;
        *str = *end - *str;
        
        str++;
        end--;
    }
}