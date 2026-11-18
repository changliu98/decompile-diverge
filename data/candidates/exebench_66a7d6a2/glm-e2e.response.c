void swapdouble(uint64_t *val) {
    // Reinterpret the 64-bit value as an array of 32-bit integers
    uint32_t *arr = (uint32_t *)val;
    
    // Read the lower 32 bits and reverse the byte order
    uint32_t temp = __builtin_bswap32(arr[0]);
    
    // Read the upper 32 bits, reverse the byte order, and store it in the lower 32 bits
    arr[0] = __builtin_bswap32(arr[1]);
    
    // Store the previously reversed lower 32 bits into the upper 32 bits
    arr[1] = temp;
}