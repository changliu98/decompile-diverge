int __cdecl test_and_set_bit(int nr, volatile unsigned __int64 *addr)
{
    // _bittestandset returns the original value of the bit (0 or 1).
    // Negating it yields 0 or -1, which is the intended semantic behavior.
    return -_bittestandset((long *)addr, nr);
}