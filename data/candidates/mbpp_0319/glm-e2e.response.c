void func0(const char *input, int *count) {
    regex_t regex;
    regmatch_t match;
    char pattern[] = "[a-zA-Z]+"; // Assuming this is the pattern at 0x2010
    int n = 0;
    
    char *buffer = (char *)alloca(strlen(input) + 1);
    strcpy(buffer, input);
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        *count = 0;
        return;
    }
    
    char *p = buffer;
    while (regexec(&regex, p, 1, &match, 0) == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;
        int len = end - start;
        
        char *word = (char *)malloc(len + 1);
        strncpy(word, p + start, len);
        word[len] = '\0';
        
        words[n++] = word;
        p += end;
    }
    
    regfree(&regex);
    *count = n;
}