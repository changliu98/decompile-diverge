void copy_string(char *dest, const char *src, int max_len) {
    int i = 0;
    char continue_copying = 0;
    
    while (i < max_len) {
        dest[i] = src[i];
        continue_copying = (src[i] != '\0');
        if (!continue_copying) {
            break;
        }
        i++;
    }
}