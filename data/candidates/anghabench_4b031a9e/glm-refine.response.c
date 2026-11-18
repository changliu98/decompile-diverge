bool valid_bo_pre_v2(long value) 
{
    // Isolate bits 4 and 2 (mask 0x14)
    int bo_bits = value & 0x14;

    switch (bo_bits) 
    {
        case 0x00: // Bits 4 and 2 are both 0
            return true;
            
        case 0x04: // Bit 2 is 1, Bit 4 is 0
            return (value & 0x02) == 0; // True if bit 1 is 0
            
        case 0x10: // Bit 2 is 0, Bit 4 is 1
            return (value & 0x08) == 0; // True if bit 3 is 0
            
        case 0x14: // Bits 4 and 2 are both 1
            return value == 0x14;       // True only if no other bits are set
    }
    
    // Fallback (logically unreachable due to the mask covering all switch cases)
    return false;
}