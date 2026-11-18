void jpq_cpuid_custom(struct cpuid_result *result, uint32_t leaf) {
    uint32_t a, b, c, d;
    
    // The inline assembly executes the CPUID instruction.
    // 'leaf' is placed in eax, and ecx is zeroed out before the call.
    __asm__ __volatile__(
        "cpuid"
        : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
        : "a"(leaf), "c"(0)
    );
    
    // Store the results into the struct
    result->eax = a;
    result->ebx = b;
    result->ecx = c;
    result->edx = d;
}