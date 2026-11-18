uLong __cdecl multmodp(uLong a, uLong b)
{
    uLong p = 0;
    uLong m = 0x80000000LL;

    while (1)
    {
        // If the current bit of 'a' is set, XOR 'b' into 'p'
        if ((a & m) != 0)
        {
            p ^= b;
            
            // If no lower bits are set in 'a', we are done
            if ((a & (m - 1)) == 0)
                break;
        }
        
        m >>= 1;
        
        // Multiply 'b' by x modulo the CRC-32 polynomial
        if ((b & 1) != 0)
            b = (b >> 1) ^ 0xEDB88320;
        else
            b >>= 1;
    }
    
    return p;
}