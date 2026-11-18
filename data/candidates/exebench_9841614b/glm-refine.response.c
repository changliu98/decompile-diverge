int __cdecl UnpackImmediate(unsigned int val, int *outByte, int *outShift)
{
    // Handle the base case where the value is exactly 0
    if (val == 0)
    {
        *outByte = 0;
        *outShift = 0;
        return 1;
    }

    // Iterate through the 15 possible 2-bit slots in a 32-bit integer
    for (int i = 0; i < 15; ++i)
    {
        // Check if the lowest 2 bits are non-zero
        if ((val & 3) != 0)
        {
            // If the remaining value fits in 1 byte, unpacking is successful
            if (val < 0x100)
            {
                *outByte = val;
                *outShift = i;
                return 1;
            }
            
            // Otherwise, it's an invalid/malformed packed immediate
            return 0;
        }
        
        // Shift right by 2 bits to check the next slot
        val >>= 2;
    }

    // Failsafe if no valid non-zero 2-bit sequence was found in the 15 slots
    return 0;
}