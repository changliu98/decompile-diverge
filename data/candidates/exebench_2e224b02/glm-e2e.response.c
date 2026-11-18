Corresponds to the data at 0x2025

void _prtl16(uint64_t val, char *buf) {
    char str[9];
    int i;
    
    // 1. Convert the integer to a hex string (8 characters for 16 bits)
    str[0] = 0;
    for (i = 1; i <= 8; i++) {
        str[i] = hex_chars[val & 0xf];
        val >>= 4;
    }
    
    // 2. Skip leading zeros
    i = 8;
    while (str[i] == '0') {
        i--;
    }
    
    // 3. If the entire value was zero, keep one '0'
    if (i == 0) {
        i++;
    }
    
    // 4. Copy the characters to the output buffer
    while (i >= 0) {
        *buf++ = str[i--];
    }
}