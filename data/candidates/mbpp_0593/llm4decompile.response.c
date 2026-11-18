char* func0(char* ip)
{
    char pattern[] = "\\.0*";
    char *newstr = malloc(strlen(ip)+1);
    regex_t re;
    int i;
    regmatch_t match;
    char *loc;

    regcomp(&re, pattern, 1);
    strcpy(newstr, ip);
    loc = newstr;
    while (!regexec(&re, loc, 1, &match, 0)) {
        memmove(loc+match.rm_so+1, loc+match.rm_eo, strlen(loc)-match.rm_eo+1);
        loc += match.rm_so+1;
    }
    regfree(&re);
    return newstr;
}