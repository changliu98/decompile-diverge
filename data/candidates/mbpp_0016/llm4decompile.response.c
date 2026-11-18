char* func0(char* text) {
    regex_t regex;
    int reti;
    char* text_local;
    char* pattern = "^[a-z]+_[a-z]+$";

    reti = regcomp(&regex, pattern, 0x01);
    reti = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        text_local = "Found a match!";
    } else {
        text_local = "Not matched!";
    }

    return text_local;
}