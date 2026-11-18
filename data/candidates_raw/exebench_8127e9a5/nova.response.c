void func0(char *s) {
    size_t len = 0;
    while (s[len]!= '\0')
        ++len;
    if (len > 0) {
        size_t top = len - 1;
        size_t i = 0;
        while (i < top) {
            char tmp = s[i];
            s[i] = s[top];
            s[top] = tmp;
            ++i;
            --top;
        }
    }
}