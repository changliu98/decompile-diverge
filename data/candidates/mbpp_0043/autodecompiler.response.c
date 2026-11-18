char *func0(char *str) {
    char *pattern = "^[a-z]+_[a-z]+$";
    regex_t regex;
    int reti;
    char msgbuf[100];
    char *result;

    reti = regcomp(&regex, pattern, 1);
    if( reti ) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Compilation error";
        goto end;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if( !reti ) {
        regfree(&regex);
        result = "Found a match!";
    }
    else if( reti == 1 ) {
        regfree(&regex);
        result = "Not matched!";
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        result = "Error occurred";
    }

end:
    return result;
}