int __cdecl sync_test_and_set_bit(int nr, volatile unsigned __int64 *addr)
{
    // _interlockedbittestandset atomically sets the bit at position 'nr' 
    // and returns the original value of that bit (0 or 1).
    // Negating the unsigned 8-bit return value converts 1 to -1 (0xFFFFFFFF) 
    // and leaves 0 as 0 (0x00000000), matching the standard boolean semantics 
    // of GCC's __sync_test_and_set_bit.
    return -(unsigned __int8)_interlockedbittestandset((volatile long *)addr, nr);
}