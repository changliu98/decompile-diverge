int scan_8long(const char *str, long *out_val) {
    int i = 0;
    long val = 0;
    
    while (1) {
        char c = str[i];
        // Subtract '0' (0x30) to get the integer value of the digit
        unsigned char digit = c - '0';
        
        // Check if the character is a valid octal digit (0-7)
        // If digit >= 8, it's either a non-digit character or '8'/'9', so we break
        if (digit >= 8) {
            break;
        }
        
        // Shift the current value left by 3 (multiply by 8) and add the new digit
        val = (val << 3) + digit;
        i++;
    }
    
    // Store the resulting long value into the output pointer
    *out_val = val;
    
    // Return the number of characters successfully parsed
    return i;
}