void break_at(char *s, char ch) {
    char *p = strchr(s, ch);
    if (p!= NULL) {
        *p = '\0';
    }
}