int8_t read_escape_control_char(int8_t c) {
    int8_t result;
    
    switch (c) {
        case 'n':  // 0x6e
            result = '\n';  // 0x0a
            break;
        case 't':  // 0x74
            result = '\t';  // 0x09
            break;
        case 'r':  // 0x72
            result = '\r';  // 0x0d
            break;
        case 'e':  // 0x65
            result = 0x1b;  // ESC character
            break;
        case 'b':  // 0x62
            result = '\b';  // 0x08
            break;
        case 'f':  // 0x66
            result = '\f';  // 0x0c
            break;
        case 'v':  // 0x76
            result = '\v';  // 0x0b
            break;
        case 'a':  // 0x61
            result = '\a';  // 0x07
            break;
        default:
            result = c;
            break;
    }
    
    return result;
}