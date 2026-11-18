void snake_upcase_char(char *c) {
    if (*c >= 'a' && *c <= 'z') {
        *c &= 0xDF; // Equivalent to *c = *c - 32 or *c = toupper(*c)
    } else if (*c == '-') {
        *c = '_';
    }
}