char* func0(char* text) {
    regex_t regex;
    int reti;
    char* text_local;
    char* match;

    text_local = text;
    reti = regcomp(&regex, "[A-Z]+[a-z]+$", 0x01);
    reti = regexec(&regex, text_local, 0, NULL, 0);
    if (!reti) {
        match = "Found a match!";
    } else {
        match = "Not matched!";
    }

    return match;
}