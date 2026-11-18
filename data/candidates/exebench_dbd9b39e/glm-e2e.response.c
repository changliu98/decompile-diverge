void stress_chop(char *str, char c) {
    char *ptr = strchr(str, c);
    if (ptr != NULL) {
        *ptr = '\0';
    }
}