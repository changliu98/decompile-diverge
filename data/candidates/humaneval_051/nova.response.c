void func0(char *s) {
    char *p = s;
    char *q = s;
    while (1) {
        if (*s!= '\0' && strchr(",.()+-/*=~%[];", *s) == NULL) {
            *p++ = *s++;
        } else {
            *p++ = '\0';
            break;
        }
    }
    *p = '\0';
}