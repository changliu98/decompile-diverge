char* ltox(uint32_t num, char* str) {
    // The hex character lookup table loaded from memory
    // Corresponds to the 8-byte values loaded at 0x11e2 and 0x11ed
    const char hex_chars[] = "FEDCBA9876543210";
    
    // Loop from i = 0 to 7
    for (int i = 0; i < 8; i++) {
        // Extract the lowest 4 bits
        int digit = num & 0xf;
        
        // Place the corresponding character from the lookup table
        // The index is reversed: 9 - i (so it iterates 9, 8, 7... 2)
        str[9 - i] = hex_chars[digit];
        
        // Shift the number right by 4 bits for the next iteration
        num >>= 4;
    }
    
    // Add the prefix and formatting
    str[0] = '0';   // 0x30
    str[1] = 'x';   // 0x78
    str[10] = '\n'; // 0xa
    str[11] = '\0'; // 0x0
    
    return str;
}