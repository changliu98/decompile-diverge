char *test_regex(char *string) {
    char *source = "a.*?b$";
    regex_t regex;
    int reti;
    char *result;

    reti = regcomp(&regex, source, 1);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Error";
        goto end;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if (!reti)
        result = "Found a match!";
    else if (reti == REG_NOMATCH)
        result = "Not matched!";
    else {
        fprintf(stderr, "Regex match error: %d\n", reti);
        result = "Error";
    }

    regfree(&regex);

end:
    return result;
}