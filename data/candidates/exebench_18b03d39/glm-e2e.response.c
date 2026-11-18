void si_swapl(uint32_t *ptr) {
    uint32_t val = *ptr;
    uint8_t *bytes = (uint8_t *)&val;
    
    // Swap bytes 0 and 3
    uint8_t temp = bytes[0];
    bytes[0] = bytes[3];
    bytes[3] = temp;
    
    // Swap bytes 1 and 2
    temp = bytes[1];
    bytes[1] = bytes[2];
    bytes[2] = temp;
    
    *ptr = val;
}