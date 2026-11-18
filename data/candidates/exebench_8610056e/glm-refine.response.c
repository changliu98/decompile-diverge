int __cdecl test_and_set_bit(int nr, volatile unsigned __int64 *addr)
{
    // Atomically sets the 'nr'-th bit of 'addr' and returns 1 if the bit was previously set, 0 otherwise.
    // The boolean result is normalized to a standard C integer representation (1 or 0).
    return _interlockedbittestandset((volatile long *)addr, nr) ? 1 : 0;
}