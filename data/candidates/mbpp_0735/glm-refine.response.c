int __cdecl func0(int n)
{
    // Base case: If n is 1, flipping both the MSB and LSB of 1 yields 1.
    // (e.g., 32-bit: 0x00000001 ^ 0x80000001 = 0x80000000, but the logic 
    // explicitly short-circuits here to return 1).
    if (n == 1)
    {
        return 1;
    }
    
    // XOR n with the result of set_middle_bits(n).
    // Assuming set_middle_bits(n) returns an integer with all bits set to 1 
    // except the MSB and LSB (e.g., 0x7FFFFFFE for 32-bit ints), this operation 
    // effectively flips only the MSB and LSB of `n` while preserving the middle bits.
    return set_middle_bits(n) ^ n;
}