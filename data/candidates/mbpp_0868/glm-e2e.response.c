int func0(const char *str) {
    int count = 0;
    const char *p = str;

    // Skip leading spaces
    while (*p == ' ') {
        p++;
    }

    int i = 0;
    int len = strlen(p);
    
    // Count non-space characters
    while (i < len) {
        if (p[i] == ' ') {
            count = 0;
        } else {
            count++;
        }
        i++;
    }

    return count;
}