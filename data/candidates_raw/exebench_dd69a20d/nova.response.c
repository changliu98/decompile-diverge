void func0(char *str, char c) {
    char *p = str, *q = str;
    while (*p) {
        *q = *p++;
        q += (*q!= c) & 1;
    }
    *q = '\0';
}