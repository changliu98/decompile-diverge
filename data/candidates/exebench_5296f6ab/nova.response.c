void charset_remove(char *s, char c) {
    char *t = s;
    char *h = s;
    for (;;) {
        if (*h!= c) {
            *t++ = *h;
        }
        if (*h == '\0') {
            break;
        }
        h++;
    }
    *t = '\0';
}