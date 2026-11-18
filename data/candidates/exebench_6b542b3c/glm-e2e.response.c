char *trim(char *str, const char *chars) {
    char *end;

    if (str == NULL) {
        return str;
    }

    end = index(str, '\0') - 1;

    while (end >= str && index(chars, *end) != NULL) {
        *end = '\0';
        end--;
    }

    return str;
}