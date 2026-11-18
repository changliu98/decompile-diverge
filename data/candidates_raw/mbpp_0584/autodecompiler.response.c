char *func0(char *str)
{
    char result[100];
    char word[100];
    regex_t regex;
    int start, end;
    regmatch_t matches[1];

    if (regcomp(&regex, "\\w+ly", 1)) {
        printf("Could not compile regex\n");
        char *r = NULL;
        return r;
    };

    if (!regexec(&regex, str, 1, matches, 0)) {
        start = matches[0].rm_so;
        end = matches[0].rm_eo;
        strncpy(word, str + start, end - start);
        word[end - start] = '\0';
        snprintf(result, 100, "%d-%d: %s", start, end, word);
        regfree(&regex);
        char *r = &result[0];
        return r;
    } else {
        regfree(&regex);
        char *r = NULL;
        return r;
    };
}