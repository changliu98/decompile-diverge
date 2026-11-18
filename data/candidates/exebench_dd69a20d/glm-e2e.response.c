void remove_all_chars(char *str, char c) {
    char *i = str;
    char *j = str;

    while (*i != '\0') {
        *j = *i;
        if (*j != c) {
            j++;
        }
        i++;
    }
    *j = '\0';
}