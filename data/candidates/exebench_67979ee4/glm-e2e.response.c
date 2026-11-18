void quaternionComposition(float a0, float a1, float a2, float a3,
                           float b0, float b1, float b2, float b3,
                           float *out0, float *out1, float *out2, float *out3) {
    // The assembly uses bitwise XOR on the highest bit to negate floats.
    // This is functionally equivalent to the unary minus operator in C.
    
    // out0 = a0*b0 - a1*b1 - a2*b2 - a3*b3
    *out0 = a0 * b0 - a1 * b1 - a2 * b2 - a3 * b3;
    
    // out1 = a0*b1 + a1*b0 + a2*b3 - a3*b2
    *out1 = a0 * b1 + a1 * b0 + a2 * b3 - a3 * b2;
    
    // out2 = a0*b2 - a1*b3 + a2*b0 + a3*b1
    *out2 = a0 * b2 - a1 * b3 + a2 * b0 + a3 * b1;
    
    // out3 = a0*b3 + a1*b2 - a2*b1 + a3*b0
    *out3 = a0 * b3 + a1 * b2 - a2 * b1 + a3 * b0;
}