int __cdecl func0(int n)
{
    // 0! and 1! both evaluate to 1
    if (n <= 1)
        return 1;
        
    // 2! evaluates to 2
    if (n == 2)
        return 2;
        
    // 3! evaluates to 6
    if (n == 3)
        return 6;
        
    // 4! evaluates to 24, last non-zero digit is 4
    if (n == 4)
        return 4;
        
    // For n >= 5, the original function returns 0. 
    // (Note: Mathematically, 5! = 120, so the last non-zero digit should be 2. 
    // This implies the original binary either contains a logic bug, 
    // or was intentionally truncated/stubbed for values >= 5).
    return 0;
}