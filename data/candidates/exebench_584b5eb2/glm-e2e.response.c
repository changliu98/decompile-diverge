char *substitute(char *str, char find, char replace) {
    char *ptr = str;
    
    if (ptr != NULL) {
        while (*ptr != '\0') {
            if (*ptr == find) {
                *ptr = replace;
                break;
            }
            ptr++;
        }
    }
    
    return str;
}