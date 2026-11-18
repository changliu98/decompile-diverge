void unscale(double *ptr, unsigned int length) {
    unsigned int i = 0;

    while (i < length) {
        ptr[i] *= 0.5;
        ++i;
    }
}