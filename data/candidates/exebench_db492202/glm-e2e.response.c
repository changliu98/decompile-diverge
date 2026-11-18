void tableset(float a, float b, int c, float *d) {
    // Multiply a and b, subtract 1.0, and truncate towards zero
    *d = truncf(a * b - 1.0f);
    
    // Assign c - 1 to the next float in the array
    *(d + 1) = (float)(c - 1);
}