const char *func0(const char *input) {
    regex_t regex;
    int ret;
    char errbuf[100];
    const char *pattern = "<pattern string at 0x2004>";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "<regcomp error msg at 0x2014>");
        return "<string at 0x202d>";
    }

    ret = regexec(&regex, input, 0, NULL, 0);
    if (ret == 0) {
        regfree(&regex);
        return "<string at 0x203f>";   // e.g. "Valid"
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return "<string at 0x204e>";   // e.g. "Invalid"
    } else {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "<format at 0x205b, e.g. \"Regex error: %s\\n\">", errbuf);
        regfree(&regex);
        return "<string at 0x2073>";   // e.g. "Error"
    }
}