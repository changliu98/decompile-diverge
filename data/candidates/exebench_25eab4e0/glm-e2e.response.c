int substitute(char *str, char find, char replace) {
    char *ptr = str;
    
    while ((ptr = strchr(ptr, find)) != NULL) {
        *ptr = replace;
        ptr++;
    }
    
    return 1;
}