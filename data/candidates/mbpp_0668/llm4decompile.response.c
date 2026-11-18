char* func0(char* string, char* charToReplace) {
    regex_t regex;
    int reti;
    regmatch_t match;
    char pattern[10];
    sprintf(pattern, "%s{2,}", charToReplace);
    reti = regcomp(&regex, pattern, 1);
    if(reti) {
        return NULL;
    }
    size_t offset = 0;
    char* outputString = strdup(string);
    while(!(reti = regexec(&regex, outputString + offset, 1, &match, 0))) {
        size_t matchStart = match.rm_so;
        size_t matchEnd = match.rm_eo;
        memmove(outputString + offset + matchStart + 1, outputString + offset + matchStart + matchEnd - matchStart, strlen(outputString) - offset - matchEnd + matchStart + 1);
        offset += matchStart + 1;
    }
    regfree(&regex);
    return outputString;
}