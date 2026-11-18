void mlVectorScaleTo(float *a, float b, float *c) {
    unsigned int i;
    for (i = 0; i < SIZE * SIZE; i++)
        c[i] = a[i] * b;
}