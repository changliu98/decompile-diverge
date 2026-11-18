char *isis_print_id(const unsigned char *id, int id_len) {
    static char id_buf[21]; // 0x15 = 21 bytes
    char *p = id_buf;
    
    // Loop for the first 6 bytes of the ID
    for (int i = 1; i <= 6; i++) {
        // Format the current byte as a 2-digit hex string
        // "%02x" is located at 0x2065
        snprintf(p, 21 - (p - id_buf), "%02x", *id++);
        
        // Advance the string pointer by the length of the newly written string
        p += strlen(p);
        
        // Insert a dot separator after the 2nd and 4th bytes
        if (i == 2 || i == 4) {
            *p++ = '.';
        }
    }
    
    // If the ID length is 7 or 8 bytes, append the 7th byte
    if (id_len >= 7) {
        // "%02x" is located at 0x205e
        snprintf(p, 21 - (p - id_buf), "%02x", *id++);
        p += strlen(p);
    }
    
    // If the ID length is exactly 8 bytes, append the 8th byte
    if (id_len == 8) {
        // "%02x" is located at 0x2064
        snprintf(p, 21 - (p - id_buf), "%02x", *id);
    }
    
    return id_buf;
}