void cmul(struct Complex *a, struct Complex *b) {
    // Calculate the real part of the product:
    // a->real * b->real - a->imag * b->imag
    double real = a->real * b->real - a->imag * b->imag;
    
    // Calculate the imaginary part of the product:
    // a->real * b->imag + a->imag * b->real
    double imag = a->real * b->imag + a->imag * b->real;
    
    // Store the results back into the first argument
    a->real = real;
    a->imag = imag;
}