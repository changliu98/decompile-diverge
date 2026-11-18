static inline int
atmc_fetch_and_add(volatile unsigned int *address, int value)
{
    int prev = value;

    __asm__ __volatile__("lock ; " "xaddl %0, %1":"+r"(value),
    "+m"(*address)::"memory");

    return prev + value;
}