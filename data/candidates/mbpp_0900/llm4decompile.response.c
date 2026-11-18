int func0(char *str) {
    regex_t regex;
    int reti;
    int reti2;

    reti = regcomp(&regex, "^5", 0);
    if (reti) {
        fprintf(*PTR_stderr_00103ff8, "Could not compile regex\n");
        return 0;
    }

    reti2 = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    if (!reti2) {
        return 1;
    }

    return 0;
}