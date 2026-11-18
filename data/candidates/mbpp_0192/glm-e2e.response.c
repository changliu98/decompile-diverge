int func0(const char *s) {
    int has_alpha = 0;
    int has_digit = 0;

    while (*s != '\0') {
        if (isalpha((unsigned char)*s)) {
            has_alpha = 1;
        }
        if (isdigit((unsigned char)*s)) {
            has_digit = 1;
        }
        s++;
    }

    return has_alpha && has_digit;
}