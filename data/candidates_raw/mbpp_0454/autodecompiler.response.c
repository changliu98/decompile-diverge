char *test_regex(char *string) {
    char *source = "\\w*z.\\w*";
    regex_t regex;
    int reti;
    char msgbuf[100];
    char *result;

    reti = regcomp(&regex, source, 1);
    if( reti ) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Regex compile error";
        goto end;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if( !reti ) {
        result = "Found a match!";
    }
    else if( reti == 1 ) {
        result = "Not matched!";
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        result = "Regex match error";
    }

end:
    return result;
}