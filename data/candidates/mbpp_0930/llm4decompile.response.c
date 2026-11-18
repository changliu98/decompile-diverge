char* func0(char* text) {
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "ab*?", 1);
    if (ret) {
        return "Error compiling regex";
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        return "Found a match!";
    } else if (ret == 1) {
        return "Not matched!";
    }

    return "Regex match failed";
}