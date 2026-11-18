void escape(char *dst, const char *src) {
    int j = 0;
    int i = 0;
    
    while (src[i] != '\0') {
        char c = src[i];
        
        switch (c) {
            case '\n':
                dst[j++] = '\\';
                dst[j++] = 'n';
                break;
            case '\t':
                dst[j++] = '\\';
                dst[j++] = 't';
                break;
            case '\\':
                dst[j++] = '\\';
                dst[j++] = '\\';
                break;
            case '\"':
                dst[j++] = '\\';
                dst[j++] = '\"';
                break;
            default:
                dst[j++] = c;
                break;
        }
        i++;
    }
    
    dst[j] = '\0';
}