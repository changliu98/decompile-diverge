char* byte2bin(uint8_t val, char *buf) {
    for (int i = 0; i < 8; i++) {
        // Extract the i-th bit (from MSB to LSB)
        int bit = val & (1 << (7 - i));
        
        // Convert to '1' or '0'
        buf[i] = bit ? '1' : '0';
    }
    
    // Null-terminate the string
    buf[8] = '\0';
    
    return buf;
}