int myrnd(unsigned int *state, unsigned int range) {
    unsigned int next = *state;
    next = next * 0x4cb2f + 1;
    
    unsigned int result;
    if (range == 0x100) {
        result = next >> 24;
    } else {
        result = next % range;
    }
    
    *state = next;
    return result;
}