char* func0(char* text) {
    regex_t regex;
    int ret = regcomp(&regex, "ab?", 1);
    if (ret) {
        return "Not matched!";
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    char* result;
    if (!ret) {
        result = "Found a match!";
    } else {
        result = "Not matched!";
    }

    regfree(&regex);
    return result;
}