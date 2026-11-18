char* func0(char* text){
    regex_t regex;
    int reti;
    char* match;

    regcomp(&regex, "ab{2,3}", 1);
    reti = regexec(&regex, text, 0, NULL, 0);
    if (!reti)
        match = "Found a match!";
    else
        match = "Not matched!";

    regfree(&regex);
    return match;
}