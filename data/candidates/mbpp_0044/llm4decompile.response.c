char* func0(char* text) {
    regex_t regex;
    int reti;
    char* retc;

    reti = regcomp(&regex, "^[[:alnum:]_]+", 0x01);
    if (reti) {
        retc = "Regex compilation error";
    } else {
        reti = regexec(&regex, text, 0, NULL, 0);
        regfree(&regex);
        if (!reti) {
            retc = "Found a match!";
        } else {
            retc = "Not matched!";
        }
    }

    return retc;
}