ulong32 __cdecl gf_mult(ulong32 a, ulong32 b, ulong32 p)
{
    ulong32 result = 0;
    ulong32 b_state = b;

    // Iterate through each of the 8 bits of 'a'
    for (int i = 0; i < 8; i++)
    {
        // If the i-th bit of 'a' is set, XOR the current 'b_state' into the result
        if ((a >> i) & 1)
            result ^= b_state;

        // Calculate the next 'b_state':
        // Multiply by 2 (left shift by 1). If the high bit (8th bit) was set, 
        // reduce it by XORing with the polynomial 'p'.
        b_state = (b_state << 1) ^ ((b_state >> 7) ? p : 0);
    }

    return result;
}