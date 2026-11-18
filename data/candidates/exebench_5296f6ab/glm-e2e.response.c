void charset_remove(char *str, char c) {
    char *dest = str;
    char *src = str;

    while (*src != '\0') {
        if (*src != c) {
            *dest = *src;
            dest++;
        }
        src++;
    }
    
    *dest = '\0';
}