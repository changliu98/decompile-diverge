void cconjf_(complex *z, complex *c) {
    c->real = z->real;
    c->imag = -z->imag;
}