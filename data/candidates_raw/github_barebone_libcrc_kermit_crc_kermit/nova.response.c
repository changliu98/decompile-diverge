unsigned short func0(const char *name, size_t name_len) {
    unsigned short hash;

    if (__builtin_memcmp(name, "GET", 3) == 0)
        hash = func0_GET();
    else
        hash = func0_POST();

    return hash;
}