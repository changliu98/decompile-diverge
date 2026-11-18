char *func0(char *string) {
    char *source = "ab{3}";
    regex_t regex;
    int reti;
    char *result;

    reti = regcomp(&regex, source, 1);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Regex compilation error";
        goto end;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if (!reti) result = "Found a match!";
    else if (reti == REG_NOMATCH) result = "Not matched!";
    else {
        fprintf(stderr, "Regex match error: %d\n", reti);
        result = "Regex match error";
    }

    regfree(&regex);

end:
    return result;
}