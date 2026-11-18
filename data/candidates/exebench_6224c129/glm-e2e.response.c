void fft2pt(float *data) {
    // Load the 4 floats from the array
    float a = data[0];
    float b = data[1];
    float c = data[2];
    float d = data[3];

    // Calculate sums
    float sum_a_c = a + c;
    float sum_b_d = b + d;

    // Calculate differences
    float diff_a_c = a - c;
    float diff_b_d = b - d;

    // Store the results back into the array
    data[0] = sum_a_c;
    data[1] = sum_b_d;
    data[2] = diff_a_c;
    data[3] = diff_b_d;
}