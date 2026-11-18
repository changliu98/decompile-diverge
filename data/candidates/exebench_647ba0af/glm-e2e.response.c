char *replace_char(char *str, char find, char replace) {
    char *ptr = strchr(str, find);
    while (ptr != NULL) {
        *ptr = replace;
        ptr = strchr(ptr + 1, find);
    }
    return str;
}