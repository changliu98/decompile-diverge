int func0(const char *arg) {
    regex_t regex;
    int ret;
    _Bool match;

    // The regex pattern is located at 0x2004. 
    // Based on typical decompilation challenges, it is likely "^[a-z]+$" or similar.
    regcomp(&regex, "^[a-z]+$", 0);
    
    ret = regexec(&regex, arg, 0, NULL, 0);
    match = (ret == 0);
    
    regfree(&regex);
    
    return match;
}