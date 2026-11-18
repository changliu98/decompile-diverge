char *test_regex(char *string) {
    char *source = "\\Bz\\B";
    regex_t regex;
    int reti;
    char msgbuf[100];
    char *result;

    reti = regcomp(&regex, source, 1);
    if( reti ) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Regex compilation error";
        return result;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if( !reti ) {
        result = "Found a match!";
        return result;
    }
    else if( reti == 1 ) {
        result = "Not matched!";
        return result;
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        result = "Regex execution error";
        return result;
    }


    regfree(&regex);

    return NULL;
}