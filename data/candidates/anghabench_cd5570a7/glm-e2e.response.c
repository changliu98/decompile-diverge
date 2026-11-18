unsigned long it_advance(unsigned long state) {
    if ((state & 0x6000400) != 0) {
        unsigned long mask = 0x6001c00;
        unsigned long itstate = state & mask;
        
        // Shift left by 1, then shift right by 17 (which is 0x11)
        itstate = (itstate << 1) | (itstate >> 17);
        
        // Mask the result back to the 0x6001c00 bits
        itstate &= mask;
        
        // Clear the original IT state bits from the state
        state &= 0xfffffffff9ffe3ff;
        
        // Merge the new IT state back into the state
        state |= itstate;
    } else {
        // Clear the bits defined by PSR_IT_MASK
        state &= ~PSR_IT_MASK;
    }
    
    return state;
}