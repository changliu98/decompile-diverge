char *replace(char *s, char old, char new) {
    char *p = strchr(s, old);
    while (p) {
        *p = new;
        p++;
        p = strchr(p, old);
    }
    return s;
}