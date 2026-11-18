void hex_to_word(char *buf, char val) {
    if (buf == 0) {
        return;
    }

    // Extract the high nibble and store it at buf[0]
    buf[0] = (val >> 4) & 0x0F;
    
    // Extract the low nibble and store it at buf[1]
    buf[1] = val & 0x0F;
    
    // Convert the nibbles to their ASCII representations
    for (int i = 0; i < 2; i++) {
        if (buf[i] > 9) {
            buf[i] += 0x37; // 0x37 is 'A' - 10 (0x41 - 0x0A)
        } else {
            buf[i] += 0x30; // 0x30 is '0'
        }
    }
}