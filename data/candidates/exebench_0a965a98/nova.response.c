int new_strcpy(char *dest, char *src, int n) {
    int i = 0;
    bool stop = false;
    while (!stop) {
        if (src[i] == '\0') {
            stop = true;
        }
        if (i < n) {
            dest[i] = src[i];
        }
        i++;
    }
    dest[i] = '\0';
    return 0;
}