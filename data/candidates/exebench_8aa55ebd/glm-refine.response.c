void __cdecl run_cpuid(uint32_t eax_0, uint32_t ecx_0, uint32_t *abcd)
{
    uint32_t a, b, c, d;

    __asm__ __volatile__(
        "cpuid"
        : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
        : "a"(eax_0), "c"(ecx_0)
    );

    abcd[0] = a;
    abcd[1] = b;
    abcd[2] = c;
    abcd[3] = d;
}