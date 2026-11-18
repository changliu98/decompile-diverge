char * func0(char *string) {
    char regex[] = "\\.0+";
    char *result = malloc(strlen(string)+1);
    regmatch_t matches[1];
    regex_t expression;
    regcomp(&expression, regex, 1);
    strcpy(result,string);
    char *offset = result;
    while(1) {
        if(regexec(&expression, offset, 1, matches, 0)) break;
        size_t len = strlen(offset);
        size_t start = matches[0].rm_so;
        size_t end = matches[0].rm_eo;
        memmove(&offset[start+1], &offset[end], len-end+1);
        offset = &offset[start+1];
    }
    regfree(&expression);
    return result;
}