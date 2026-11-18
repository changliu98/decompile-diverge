char *strcpy_x86_64_fast(char *dest, const char *src) {
    char *d = dest;
    const char *s = src;
    char c;

    do {
        c = *s++;
        *d++ = c;
    } while (c != '\0');

    // The following lines correspond to the dead store instructions 
    // at the end of the assembly (mov %esi, %eax, etc.). 
    // They are likely artifacts from an unoptimized or intermediate build.
    int var_14 = (int)(long)s;
    int var_18 = (int)(long)d;

    return dest;
}