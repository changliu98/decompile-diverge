void __cdecl make_double_bigendian(double *x)
{
    union {
        double d;
        uint8_t b[8];
    } v;
    
    int i;
    
    // Load the double into the union
    v.d = *x;
    
    // Reverse the bytes (swap bytes from the ends towards the center)
    for (i = 0; i < 4; i++) {
        uint8_t temp = v.b[i];
        v.b[i] = v.b[7 - i];
        v.b[7 - i] = temp;
    }
    
    // Store the big-endian double back
    *x = v.d;
}