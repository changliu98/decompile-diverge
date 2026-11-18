size_t sdsull2str(char *s, unsigned long long v) {
    char *p = s;
    size_t l;

    // Convert number to string in reverse order
    do {
        *p++ = '0' + (v % 10);
        v /= 10;
    } while (v != 0);

    // Calculate the length of the string
    l = p - s;

    // Null-terminate the string
    *p = '\0';
    p--;

    // Reverse the string in-place
    while (s < p) {
        char t = *s;
        *s = *p;
        *p = t;
        s++;
        p--;
    }

    return l;
}