static const char *func0(const char *s, int *base) {
    const char *p;
    if (s[0] == '0') {
        switch (s[1]) {
        case 'x':
            *base = 16;
            break;
        case 't':
            *base = 10;
            break;
        case 'o':
            *base = 8;
            break;
        default:
            *base = 10;
            p = s;
            goto end;
        }
        s += 2;
    } else {
        *base = 10;
        p = s;
    }
end:
    return p;
}