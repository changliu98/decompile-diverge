int func0(char *input) {
    regex_t re;
    int status;
    int reti;
    char *result;
    reti = regcomp(&re, "^[a-zA-Z0-9]+[a-zA-Z0-9-_.]*@[a-zA-Z0-9-_]+(\\.[a-zA-Z0-9]+){1,}$",
                   REG_EXTENDED | REG_NOSUB);
    status = regexec(&re, input, 0, NULL, 0);
    regfree(&re);
    if (status == REG_NOERROR) {
        return 1;
    } else {
        return 0;
    }
}