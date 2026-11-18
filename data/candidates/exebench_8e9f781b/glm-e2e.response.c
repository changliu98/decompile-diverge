void cftf040(float *data) {
    // The function operates on 8 floats (32 bytes) in-place.
    // It computes the sums and differences of pairs of complex numbers.
    
    // data[0] and data[1] represent the real and imaginary parts of the 1st complex number
    // data[4] and data[5] represent the real and imaginary parts of the 3rd complex number
    float a0 = data[0] + data[4];
    float a1 = data[1] + data[5];
    float a2 = data[0] - data[4];
    float a3 = data[1] - data[5];
    
    // data[2] and data[3] represent the real and imaginary parts of the 2nd complex number
    // data[6] and data[7] represent the real and imaginary parts of the 4th complex number
    float b0 = data[2] + data[6];
    float b1 = data[3] + data[7];
    float b2 = data[2] - data[6];
    float b3 = data[3] - data[7];
    
    // Combine and store the results back into the array
    data[0] = a0 + b0;
    data[1] = a1 + b1;
    data[2] = a2 - b3;
    data[3] = a3 + b2;
    
    data[4] = a0 - b0;
    data[5] = a1 - b1;
    data[6] = a2 + b3;
    data[7] = a3 - b2;
}