char* func0(char* text) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "\\w+\\S*$", 1);
    if(reti) {
        return "Regex compilation failed";
    }
    regmatch_t match;
    reti = regexec(&regex, text, 1, &match, 0);
    if(!reti) {
        regfree(&regex);
        return "Found a match!";
    }
    regfree(&regex);
    return "Not matched!";
}