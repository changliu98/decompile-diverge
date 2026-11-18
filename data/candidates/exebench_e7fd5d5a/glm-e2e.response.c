void basename_discriminant(const char *path, long *hash, long *length) {
    const char *base = strrchr(path, '/');
    if (base == NULL) {
        base = path;
    } else {
        base++;
    }

    *length = 0;
    *hash = 0;

    while (*base != '\0') {
        *hash = *hash * 33 + *base;
        base++;
        (*length)++;
    }
}