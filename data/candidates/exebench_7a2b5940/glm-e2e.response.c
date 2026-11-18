char *tcp_strflags(char *buf, int flags) {
    const char *flag_chars = "FSRPAUEC"; // String located at 0x2004
    char *p = buf;
    
    for (int i = 0; i < 8; i++) {
        if (flags & (1 << i)) {
            *p++ = flag_chars[i];
        }
    }
    
    *p = '\0';
    return buf;
}