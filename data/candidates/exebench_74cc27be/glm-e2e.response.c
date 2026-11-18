void Q_bstrcpy(char *dst, char *src) {
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0';
}