char * func0(char * str) {
    int i;
    int offset;
    int error;
    regex_t regex;
    regmatch_t match[2];
    char * local_str;

    local_str = malloc(strlen(str)+1);
    strcpy(local_str, str);

    error = regcomp(&regex, " ?\\([^)]+\\)", 1);
    if (error) {
        return local_str;
    }

    while (!error) {
        error = regexec(&regex, local_str, 2, match, 0);
        if (!error) {
            offset = match[0].rm_eo - match[0].rm_so;
            memmove(local_str+match[0].rm_so, local_str+match[0].rm_eo, strlen(local_str)-match[0].rm_eo+1);
        }
    }

    regfree(&regex);
    return local_str;
}