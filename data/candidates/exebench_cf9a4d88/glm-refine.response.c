int __cdecl FABSQ(v128_t *rd, const v128_t *rs2)
{
    // Clear the most significant bit (sign bit) of the lower 64 bits.
    // Note: The original decompiled code clears the MSB of *rs2 (rd[0]), 
    // not rs2[1]. This behavior is preserved exactly.
    rd->lo = rs2->lo & 0x7FFFFFFFFFFFFFFFULL;
    
    // Copy the upper 64 bits unaltered.
    rd->hi = rs2->hi;
    
    return 1;
}