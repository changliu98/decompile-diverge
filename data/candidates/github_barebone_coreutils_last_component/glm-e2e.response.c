char *last_component(char *path) {
    char *p = path;
    char *last = p;
    char seen_slash = 0;

    // Skip leading slashes
    while (*p == '/') {
        p++;
    }

    // Find the last component
    while (*p != '\0') {
        if (*p == '/') {
            seen_slash = 1;
        } else if (seen_slash) {
            last = p;
            seen_slash = 0;
        }
        p++;
    }

    return last;
}