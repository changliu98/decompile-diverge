void ToIUPAC(char *str, int strict) {
    if (strict != 0) {
        while (*str != '\0') {
            if (strchr("ATUGCYRSWKMBDHVN", *str) == NULL && 
                *str != ' ' && 
                *str != '.' && 
                *str != '_' && 
                *str != '-' && 
                *str != '~') {
                *str = 'N';
            }
            str++;
        }
    } else {
        while (*str != '\0') {
            if (strchr("ATUGCYRSWKMBDHVN", *str) == NULL) {
                *str = 'N';
            }
            str++;
        }
    }
}