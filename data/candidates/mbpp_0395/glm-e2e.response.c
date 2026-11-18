char func0(const char *str) {
    int counts[256] = {0};
    char unique_chars[1024];
    int unique_count = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (counts[(unsigned char)c] == 0) {
            unique_chars[unique_count++] = c;
        }
        counts[(unsigned char)c]++;
    }

    for (int i = 0; i < unique_count; i++) {
        char c = unique_chars[i];
        if (counts[(unsigned char)c] == 1) {
            return c;
        }
    }

    return '\0';
}