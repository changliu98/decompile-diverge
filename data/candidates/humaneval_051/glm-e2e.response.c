void func0(char *str) {
    const char *chars = " \t\n";
    char *ptr = str;
    
    while (*str != '\0') {
        if (strchr(chars, *str) == NULL) {
            *ptr = *str;
            ptr++;
        }
        str++;
    }
    *ptr = '\0';
}