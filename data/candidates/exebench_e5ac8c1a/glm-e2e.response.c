void rifft1pt(float *p, float scale) {
    float real = p[0];
    float imag = p[1];
    float sum = real + imag;
    float diff = real - imag;
    
    p[0] = scale * sum;
    p[1] = scale * diff;
}