void to_hex(long val, char *buf) {
    // The hex characters "0123456789abcdef" are loaded from memory
    // (specifically from the .rodata section at _IO_stdin_used+0x10)
    static const char hex_chars[] = "0123456789abcdef";
    
    // Loop from 3 down to 0
    for (int i = 3; i >= 0; i--) {
        // Get the last 4 bits of val and use it to index hex_chars
        buf[i] = hex_chars[val % 16];
        
        // Shift val right by 4 bits (arithmetic shift)
        val >>= 4;
    }
    
    // Null-terminate the string
    buf[4] = '\0';
}