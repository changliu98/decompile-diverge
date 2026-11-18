char* unmakemask(int mask, char* str) {
    int i = 0;
    
    if (mask & 1) {
        str[i++] = 'c'; // 0x63
    }
    if (mask & 2) {
        str[i++] = 'r'; // 0x72
    }
    if (mask & 4) {
        str[i++] = 'l'; // 0x6c
    }
    
    str[i] = '\0';
    
    return str;
}