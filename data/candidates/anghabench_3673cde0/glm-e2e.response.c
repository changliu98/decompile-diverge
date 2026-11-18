float modff(float x, float *iptr) {
    // Reinterpret the float bits as an unsigned 32-bit integer
    uint32_t u = *(uint32_t*)&x;
    
    // Extract the exponent (bits 23-30) and subtract the bias (127)
    int e = (int)((u >> 23) & 0xFF) - 127;
    
    // Case 1: Exponent is large enough that the number has no fractional part
    if (e >= 23) {
        *iptr = x;
        
        // Check for NaN or Infinity (exponent == 128)
        if (e == 128 && (u << 9) != 0) {
            return x; // NaN returns itself
        }
        
        // For Infinity or large integers, fractional part is 0.0 (preserving sign)
        u &= 0x80000000;
        return *(float*)&u;
    } 
    // Case 2: Exponent is small enough that the number has no integer part
    else if (e < 0) {
        *iptr = *(float*)&(uint32_t){u & 0x80000000}; // 0.0 with original sign
        return x;
    } 
    // Case 3: The number has both integer and fractional parts
    else {
        // Create a mask for the fractional bits
        uint32_t mask = 0x7FFFFF >> e;
        
        // If there are no fractional bits set, the number is effectively an integer
        if ((u & mask) == 0) {
            *iptr = x;
            u &= 0x80000000;
            return *(float*)&u;
        } 
        
        // Mask out the fractional bits to get the integer part
        u &= ~mask;
        *iptr = *(float*)&u;
        
        // Subtract the integer part from the original number to get the fractional part
        return x - *(float*)&u;
    }
}