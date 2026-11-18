void cpuid(unsigned int cpu_info[4], const unsigned int cpuid_input) {
    asm("cpuid"
        : "=a"(cpu_info[0]), "=b"(cpu_info[1]), "=c"(cpu_info[2]), "=d"(cpu_info[3])
        : "a"(cpuid_input), "c"(0));
}