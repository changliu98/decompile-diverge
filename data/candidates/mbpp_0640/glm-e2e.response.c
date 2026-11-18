char* func0(char* arg) {
    char* str = malloc(strlen(arg) + 1);
    strcpy(str, arg);

    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", 1) == 0) {
        regmatch_t match;
        while (regexec(&regex, str, 2, &match, 0) == 0) {
            int rm_so = match.rm_so;
            int rm_eo = match.rm_eo;
            char* start = str + rm_so;
            char* end = str + rm_eo;
            memmove(start, end, strlen(str) - rm_eo + 1);
        }
        regfree(&regex);
    }
    
    return str;
}