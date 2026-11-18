const char *_getbase(const char *s, int *base) {
    if (s[0] == '0') {
        char c = s[1];
        if (c == 'x' || c == 'X') {
            *base = 16;
            return s + 2;
        } else if (c == 'b' || c == 'B') {
            *base = 8;
            return s + 2;
        } else {
            *base = 10;
            return s;
        }
    } else {
        *base = 10;
        return s;
    }
}