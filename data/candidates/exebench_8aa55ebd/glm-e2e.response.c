void run_cpuid(uint32_t eax_in, uint32_t ecx_in, struct cpuid_result *result) {
    uint32_t a = eax_in;
    uint32_t c = ecx_in;
    uint32_t b = 0;
    uint32_t d = 0;

    __asm__ __volatile__ (
        "cpuid"
        : "+a" (a), "+b" (b), "+c" (c), "=d" (d)
    );

    result->eax = a;
    result->ebx = b;
    result->ecx = c;
    result->edx = d;
}