float abs_sf(float *x) {
    float val = *x;
    
    // Clear the sign bit to get the absolute value.
    // This is equivalent to bitwise ANDing the float's representation with 0x7FFFFFFF.
    *(uint32_t*)&val &= 0x7FFFFFFF;
    
    return val;
}