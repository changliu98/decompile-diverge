size_t modp_rtrim(char *str, size_t len) {
    while (len > 0 && ((str[len - 1] == ' ') || (str[len - 1] == '\n') || (str[len - 1] == '\t') || (str[len - 1] == '\r'))) {
        str[len - 1] = '\0';
        len--;
    }
    return len;
}