int func0(char *s) {
    regex_t r;
    int n;
    char buf[100];
    n = regcomp(&r, "^[a-z]+[0-9]*$", 0);
    if (n!= 0) {
        fprintf(stderr, "regcomp failed\n");
        exit(0);
    }
    n = regexec(&r, s, 0, NULL, 0);
    regfree(&r);
    if (n == 0)
        return 1;
    else
        return 0;
}