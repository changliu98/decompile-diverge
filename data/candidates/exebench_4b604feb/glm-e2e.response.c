void ml_multiply_mat2_mat2(float *a, float *b, float *out) {
    // The assembly uses local stack variables to store intermediate results.
    // We can represent this directly with local variables.
    float res0, res1, res2, res3;

    // out[0] = a[0] * b[0] + a[1] * b[2]
    res0 = a[0] * b[0] + a[1] * b[2];
    
    // out[1] = a[0] * b[1] + a[1] * b[3]
    res1 = a[0] * b[1] + a[1] * b[3];
    
    // out[2] = a[2] * b[0] + a[3] * b[2]
    res2 = a[2] * b[0] + a[3] * b[2];
    
    // out[3] = a[2] * b[1] + a[3] * b[3]
    res3 = a[2] * b[1] + a[3] * b[3];

    // Store the results into the output array
    out[0] = res0;
    out[1] = res1;
    out[2] = res2;
    out[3] = res3;
}