long long vcomma(const char *str, long long len, long long pos, char c) {
    if (pos == len) {
        return -(pos + 1);
    }
    
    if (str[pos] == ',') {
        return pos;
    }
    
    while (pos < len) {
        unsigned char ch = str[pos];
        
        // Check for whitespace characters: \t (0x09), \n (0x0A), \r (0x0D), space (0x20)
        if (ch == '\t' || ch == '\n' || ch == '\r' || ch == ' ') {
            // Skip whitespace
        } else if (ch == ',') {
            return pos;
        } else if (ch == c) {
            return pos;
        } else {
            return -(pos + 1);
        }
        
        pos++;
    }
    
    return -(pos + 1);
}