void make_double_bigendian(double *d) {
    // Create a local copy of the double
    double val = *d;
    
    // Reinterpret the 8 bytes of the double as a 64-bit integer
    uint64_t *val_ptr = (uint64_t *)&val;
    
    // Reverse the bytes to convert from little-endian to big-endian
    *val_ptr = ((*val_ptr & 0x00000000000000FFULL) << 56) |
               ((*val_ptr & 0x000000000000FF00ULL) << 40) |
               ((*val_ptr & 0x00000000FF000000ULL) << 24) |
               ((*val_ptr & 0x000000FF00000000ULL) << 8)  |
               ((*val_ptr & 0x0000FF0000000000ULL) >> 8)  |
               ((*val_ptr & 0x00FF000000000000ULL) >> 24) |
               ((*val_ptr & 0xFF00000000000000ULL) >> 40) |
               ((*val_ptr & 0xFF00000000000000ULL) >> 56); // Note: 0xFF...ULL >> 56 is sufficient for the last byte

    // Write the byte-swapped value back to the pointer
    *d = val;
}