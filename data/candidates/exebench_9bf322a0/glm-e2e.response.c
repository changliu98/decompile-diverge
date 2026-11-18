char* my_strncpy(char *dest, const char *src, int n) {
    int i = -1;
    char continue_loop;

    do {
        i++;
        continue_loop = src[i] != '\0';
        if (continue_loop) {
            continue_loop = i < n;
        }
        
        if (continue_loop) {
            dest[i] = src[i];
        }
    } while (continue_loop);

    dest[i] = '\0';
    return dest;
}