void escape(char *dst, const char *src) {
    int dst_idx = 0;
    int src_idx = 0;
    
    while (dst[dst_idx] != '\0') {
        char c = src[src_idx];
        if (c == '\0') {
            break;
        }
        
        if (c == '\t') {
            dst[dst_idx++] = '\\';
            dst[dst_idx++] = 't';
        } else if (c == '\n') {
            dst[dst_idx++] = '\\';
            dst[dst_idx++] = 'n';
        } else {
            dst[dst_idx++] = c;
        }
        
        src_idx++;
    }
}