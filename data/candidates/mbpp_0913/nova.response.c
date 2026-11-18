int func0(char *str) {
    regex_t re;
    int status;
    int reti;
    char *p;
    p = str;
    reti = regcomp(&re, "^[a-zA-Z0-9]+[\\._]?[a-zA-Z0-9]+[@][a-zA-Z0-9]+[\\.][a-zA-Z0-9]+$", 0);
    status = regexec(&re, p, 0, NULL, 0);
    regfree(&re);
    if (status!= 0)
        return 1;
    else
        return 0;
}