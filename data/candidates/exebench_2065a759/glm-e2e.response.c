int set_filename(char *dst, char *src) {
    while (*src != '\0') {
        if (*src == '/') {
            *dst = '\0';
            return 2;
        }
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return 1;
}