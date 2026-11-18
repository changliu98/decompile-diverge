int last_slash(const char *str, int *count, int *pos) {
    int slash_count = 0;
    int last_pos = 0;
    int i = 0;
    
    while (str[i] != '\0' && i < 256) {
        if (str[i] == '/') {
            slash_count++;
            last_pos = i;
        }
        i++;
    }
    
    *count = slash_count;
    *pos = i;
    
    return last_pos;
}