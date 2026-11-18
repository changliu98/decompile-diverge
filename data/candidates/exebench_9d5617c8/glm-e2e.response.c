void ifft2pt(float* data, float scale) {
    // Load the 4 floats from the data pointer
    // data[0] and data[1] represent the real and imaginary parts of the first complex number
    // data[2] and data[3] represent the real and imaginary parts of the second complex number
    float a = data[0];
    float b = data[1];
    float c = data[2];
    float d = data[3];

    // Perform 2-point Inverse FFT butterfly operations
    float real_sum = a + c;
    float imag_sum = b + d;
    float real_diff = a - c;
    float imag_diff = b - d;

    // Store the results back to the data pointer, scaled by the 'scale' factor
    data[0] = scale * real_sum;
    data[1] = scale * imag_sum;
    data[2] = scale * real_diff;
    data[3] = scale * imag_diff;
}