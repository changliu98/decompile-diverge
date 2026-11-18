void atomic_retain(int *ptr) {
    __asm__ __volatile__("lock addl $1, (%0)" : : "r"(ptr) : "memory");
}