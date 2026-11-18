void string_rip(char *s, char *t) {
    char *b = s;
    while (*s) {
        char *c = t;
        int found = 0;
        while (*c) {
            if (*s == *c) {
                found = 1;
                break;
            }
            c++;
        }
        if (found)
            s++;
        else
            *b++ = *s++;
    }
    *b = '\0';
}