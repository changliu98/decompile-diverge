int func0(char *str, char c, char r) {
    char *p = NULL;
    for (p = str; (p = strchr(p, c))!= NULL; p++)
        *p = r;
    return 1;
}