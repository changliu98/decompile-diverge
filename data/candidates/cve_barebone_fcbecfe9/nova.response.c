static void *mrbc_raw_realloc(void *ptr, int size) {
    void *p;
    void **pp;

    if (ptr && size == 0) {
        free(ptr);
        p = NULL;
    } else {
        p = realloc(ptr, size);
    }
    while (p == NULL) {
        p = realloc(ptr, size);
    }
    return p;
}