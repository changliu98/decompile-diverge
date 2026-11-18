static inline unsigned long atomic_fetch_and(struct cpu_state *cpu, unsigned long mask) {
    unsigned long ret = cpu->evmask;
    cpu->evmask &= mask;
    return ret;
}