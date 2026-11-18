void do_cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a = *eax;
    uint32_t c = *ecx;
    uint32_t b, d;

    __asm__ __volatile__(
        "cpuid"
        : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
        : "a"(a), "c"(c)
    );

    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}