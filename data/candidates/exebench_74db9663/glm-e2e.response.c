void zadd(struct complex *a, struct complex *b, struct complex *out) {
    // Add real parts
    out->real = a->real + b->real;
    
    // Add imaginary parts
    out->imag = a->imag + b->imag;
}