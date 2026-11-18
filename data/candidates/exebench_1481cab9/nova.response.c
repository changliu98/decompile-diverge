void snake_upcase_char(char *c) {
    if (*c >= 'a' && *c <= 'z') {
        *c = *c - 32;
    } else if (*c == '-') {
        *c = '_';
    }
}