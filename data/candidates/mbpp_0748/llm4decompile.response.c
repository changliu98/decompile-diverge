void func0(char *str1, char *result)
{
    regex_t regex;
    regmatch_t matches[3];
    char buffer[1024];
    char *cursor;

    regcomp(&regex, "([a-z])([A-Z])", 1);
    strcpy(buffer, str1);
    cursor = buffer;
    *result = 0;

    while (!regexec(&regex, cursor, 3, matches, 0)) {
        strncat(result, cursor, matches[1].rm_eo);
        strcat(result, " ");
        cursor += matches[2].rm_so;
    }

    strcat(result, cursor);
    regfree(&regex);
}