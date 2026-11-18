unsigned int __cdecl render_uint32(unsigned int n, char *buff)
{
    // Handle the zero case explicitly
    if (n == 0)
    {
        buff[0] = '0';
        return 1;
    }

    unsigned int len = 0;
    unsigned int na = n;

    // Process each 4-bit nibble until the number becomes zero
    while (na)
    {
        // Extract the lowest 4 bits, map to hex char, and store in buffer
        buff[len] = HEX_CHARS[na & 0xF];
        
        // Advance the buffer index
        len++;
        
        // Shift right by 4 bits to process the next nibble
        na >>= 4;
    }

    return len;
}