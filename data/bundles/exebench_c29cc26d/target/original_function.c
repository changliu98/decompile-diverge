static inline char* strcpy_x86_64_fast(char *__restrict__ s1, const char *__restrict__ s2)
{
    int rsrc, rdst;
    __asm__ __volatile__(
        "1: \tlodsb\n\t;"
        "stosb\n\t;"
        "testb %%al,%%al\n\t;"
        "jne 1b;"
        : "=&S" (rsrc), "=&D" (rdst)
        : "0" (s2), "1" (s1)
        );
    return s1;
}