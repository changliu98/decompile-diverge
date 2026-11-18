void break_atr(char *str, char c) {
    char *ptr = strrchr(str, c);
    if (ptr != NULL) {
        *ptr = '\0';
    }
}