int readUTF8(const char *str, int len, int pos, int *bytes_read) {
    int code_point = 0;
    
    // 2-byte sequence
    if (pos < len - 1 && 
        (str[pos] & 0xE0) == 0xC0 && 
        (str[pos + 1] & 0xC0) == 0x80) {
        
        *bytes_read = 2;
        code_point = (str[pos] & 0x1F) << 6;
        code_point += (str[pos + 1] & 0x3F);
        
        if (code_point < 0x80) {
            code_point = 0;
        }
    } 
    // 3-byte sequence
    else if (pos < len - 2 && 
             (str[pos] & 0xF0) == 0xE0 && 
             (str[pos + 1] & 0xC0) == 0x80 && 
             (str[pos + 2] & 0xC0) == 0x80) {
        
        *bytes_read = 3;
        code_point = (str[pos] & 0x0F) << 6;
        code_point += (str[pos + 1] & 0x3F);
        code_point <<= 6;
        code_point += (str[pos + 2] & 0x3F);
        
        if (code_point < 0x800) {
            code_point = 0;
        }
    } 
    // 4-byte sequence
    else if (pos < len - 3 && 
             (str[pos] & 0xF8) == 0xF0 && 
             (str[pos + 1] & 0xC0) == 0x80 && 
             (str[pos + 2] & 0xC0) == 0x80 && 
             (str[pos + 3] & 0xC0) == 0x80) {
        
        *bytes_read = 4;
        code_point = (str[pos] & 0x07) << 6;
        code_point += (str[pos + 1] & 0x3F);
        code_point <<= 6;
        code_point += (str[pos + 2] & 0x3F);
        code_point <<= 6;
        code_point += (str[pos + 3] & 0x3F);
        
        if (code_point < 0x10000) {
            code_point = 0;
        }
    }
    
    return code_point;
}