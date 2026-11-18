void basename_discriminant(const char *filename, uint32_t *hash, size_t *len)
{
    const char *base = strrchr(filename, '/');
    if (base)
        base++;
    else
        base = filename;

    *len = 0;
    *hash = 0;
    while (*base) {
        *hash *= 33;
        *hash += *base;
        (*len)++;
        base++;
    }
}