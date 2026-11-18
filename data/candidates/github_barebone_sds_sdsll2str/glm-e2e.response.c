size_t sdsll2str(char *s, long long value) {
    char *p = s;
    unsigned long long uv;
    size_t len;

    if (value < 0) {
        if (value == INT64_MIN) {
            uv = (unsigned long long)INT64_MIN;
        } else {
            uv = (unsigned long long)(-value);
        }
    } else {
        uv = (unsigned long long)value;
    }

    do {
        *p++ = '0' + (char)(uv % 10);
        uv /= 10;
    } while (uv != 0);

    if (value < 0) {
        *p++ = '-';
    }

    len = (size_t)(p - s);
    *p = '\0';

    p--;
    while (s < p) {
        char temp = *s;
        *s = *p;
        *p = temp;
        s++;
        p--;
    }

    return len;
}