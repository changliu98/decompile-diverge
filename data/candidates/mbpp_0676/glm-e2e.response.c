char *func0(const char *arg) {
    size_t len = strlen(arg);
    char *res = malloc(len + 1);
    if (res == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isgraph((unsigned char)arg[i])) {
            res[j++] = arg[i];
        }
    }
    res[j] = '\0';
    
    return res;
}