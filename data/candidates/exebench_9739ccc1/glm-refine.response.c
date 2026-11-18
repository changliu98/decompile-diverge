void __cdecl set_stimulus(unsigned __int8 *dst, char *p)
{
    // Iterate over the string until the null terminator is reached
    while ( *p )
    {
        // Check if the character is an ASCII digit between '0' and '7'
        if ( *p >= '0' && *p <= '7' )
        {
            // Convert the ASCII character to its integer value (0-7)
            int bit_pos = *p - '0';
            
            // Clear (set to 0) the corresponding bit in the destination byte.
            // The bitwise NOT (~) creates a mask with all bits set to 1 except 
            // the target bit, and the AND (&=) applies it to clear just that bit.
            *dst &= ~(1 << bit_pos);
        }
        ++p;
    }
}