char *my_strncpy(char *dest, const char *src, int n) {
    int i = 0;
    bool end = false;
    while (!end) {
        if (i < n) {
            end = (src[i] == '\0');
        }
        dest[i] = src[i];
        i++;
    }
    if (i >= n) {
        dest[i] = '\0';
    }
    return dest;
}