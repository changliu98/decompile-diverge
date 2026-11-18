int __cdecl test_and_change_bit(int nr, volatile unsigned __int64 *addr)
{
    // _bittestandcomplement returns the original value of the bit (0 or 1).
    // The '-' operator maps 0 -> 0 and 1 -> -1, which matches the standard 
    // boolean return convention of Linux kernel test_and_change_bit().
    return -_bittestandcomplement((long *)addr, nr);
}