int str_linecount(const char *str, int max_len, int *col) {
    int lines = 1;
    
    if (*str == '\0') {
        return lines;
    }
    
    do {
        if (*str == '\n') {
            lines++;
            *col = 0;
        } else {
            *col += 1;
            if (*col >= max_len) {
                lines++;
                *col = 0;
            }
        }
        str++;
    } while (*str != '\0');
    
    return lines;
}