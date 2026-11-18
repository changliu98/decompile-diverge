void rfft1pt(float *data) {
    float real = data[0];
    float imag = data[1];
    
    float sum = real + imag;
    float diff = real - imag;
    
    data[0] = sum;
    data[1] = diff;
}