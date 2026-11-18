void __cdecl basename_discriminant(const char *filename, long *h, long *len)
{
    const char *base;

    // Find the last occurrence of '/' (ASCII 47) to isolate the basename
    char *slash = strrchr(filename, '/');
    if (slash) {
        base = slash + 1;
    } else {
        base = filename;
    }

    // Initialize output variables
    *len = 0LL;
    *h = 0LL;

    // Compute a djb2-like hash and the length of the basename
    while (*base)
    {
        *h = *h * 33LL + *base;
        base++;
        ++*len;
    }
}