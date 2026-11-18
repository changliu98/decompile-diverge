size_t base_len(const char *path) {
    size_t len = strlen(path);
    
    // Strip trailing slashes
    while (len >= 1 && path[len - 1] == '/') {
        len--;
    }
    
    return len;
}