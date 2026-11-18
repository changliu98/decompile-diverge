float nabs_sf(float *x) {
    float f = *x;
    // The next two lines correspond to the redundant movss instructions
    // which are likely artifacts of unoptimized compilation.
    f = f;
    f = f;
    
    // Clear the sign bit to get the absolute value
    f = fabsf(f);
    
    // Set the sign bit to make it negative
    f = -f;
    
    return f;
}