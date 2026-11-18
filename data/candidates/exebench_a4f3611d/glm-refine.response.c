int __cdecl sync_test_and_change_bit(int nr, volatile unsigned __int64 *addr)
{
    int oldbit;
    __asm__ __volatile__(
        "lock btc %2, %1\n\t"
        "sbb %0, %0"
        : "=r" (oldbit)
        : "m" (*addr), "Ir" (nr)
        : "cc", "memory"
    );
    return oldbit;
}