void func0(char *s, char ch) {
    char *p = strchr(s, ch);
    if (p!= NULL) {
        *p = '\0';
    }
}