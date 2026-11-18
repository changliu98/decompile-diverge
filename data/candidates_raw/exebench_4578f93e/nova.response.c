char *func0(char *dest, const char *src, int n) {
    char *d = dest;
    int i = 0;
    bool end = false;
    while (i < n) {
        end = (*src)? true : false;
        if (end) {
            *d++ = *src++;
            i++;
        } else {
            break;
        }
    }
    *d = '\0';
    return dest;
}