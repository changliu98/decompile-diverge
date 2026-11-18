static inline unsigned long func0(struct cpu_state *cpu, unsigned long mask) {
    unsigned long ret = cpu->evmask;
    cpu->evmask &= mask;
    return ret;
}