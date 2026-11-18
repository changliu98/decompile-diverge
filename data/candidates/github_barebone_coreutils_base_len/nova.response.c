static size_t base_len(const char *path) {
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