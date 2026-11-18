char* i2hs(uint32_t num, char* buffer) {
    const char* hex_chars = "0123456789abcdef";
    char temp[36];
    char* temp_ptr = temp;
    char* buf_ptr = buffer;
    
    *temp_ptr = 0;
    
    // Convert integer to hex string in reverse order
    while (num > 0) {
        *temp_ptr = hex_chars[num & 0xf];
        temp_ptr++;
        num >>= 4;
    }
    
    // If the number was 0, the loop didn't run, so add a '0'
    if (*temp_ptr == 0) {
        *temp_ptr = '0';
        temp_ptr++;
    }
    
    // Reverse the string and copy it to the output buffer
    temp_ptr--; // Skip the null terminator
    do {
        *buf_ptr = *temp_ptr;
        buf_ptr++;
        temp_ptr--;
    } while (*(buf_ptr - 1) != 0);
    
    return buffer;
}