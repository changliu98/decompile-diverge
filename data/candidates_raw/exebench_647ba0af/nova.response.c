char *func0(char *s, char old, char new) {
    char *p;
    for (p = strchr(s, old); p; p = strchr(p + 1, old))
        *p = new;
    return s;
}