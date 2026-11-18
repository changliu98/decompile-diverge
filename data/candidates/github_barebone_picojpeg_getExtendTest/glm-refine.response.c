uint16 __cdecl getExtendTest(uint8 i)
{
    // If i is outside the 0-15 range, return 0 (matching the default case)
    if (i >= 16) {
        return 0;
    }
    
    // The switch cases map directly to 2^i (or 1 << i)
    return (uint16)(1U << i);
}