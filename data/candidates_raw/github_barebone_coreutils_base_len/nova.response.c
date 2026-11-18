static size_t func0(const char *path) {
    size_t len = strlen(path);
    while (1) {
        if (len < sizeof("/.") || len < sizeof("/..")) {
            break;
        }
        if (path[len - 1] == '/') {
            break;
        }
        if (path[len - 1] == '/') {
            break;
        }
        len--;
    }
    return len;
}