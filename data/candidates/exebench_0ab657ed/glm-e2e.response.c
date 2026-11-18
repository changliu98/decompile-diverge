void run_cpuid(uint32_t leaf, uint32_t subleaf, struct cpuid_result *result) {
    uint32_t a = leaf;
    uint32_t b = 0;
    uint32_t c = subleaf;
    uint32_t d = 0;

    __asm__ __volatile__(
        "cpuid"
        : "+a" (a), "+b" (b), "+c" (c), "=d" (d)
    );

    result->eax = a;
    result->ebx = b;
    result->ecx = c;
    result->edx = d;
}