char *func0(char *str) {
    regex_t re;
    int re_err;
    char msgbuf[100];
    char *ret;

    if ((re_err = regcomp(&re, "^[a-z]$|^([a-z]).*\\1$", 1))) {
        fprintf(stderr, "Could not compile regex\n");
        ret = "Invalid";
        goto end;
    }

    if (!(re_err = regexec(&re, str, 0, NULL, 0))) {
        regfree(&re);
        ret = "Valid";
        goto end;
    }
    else if (re_err == 1) {
        regfree(&re);
        ret = "Invalid";
        goto end;
    }
    else {
        regerror(re_err, &re, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&re);
        ret = "Invalid";
    }

end:
    return ret;
}