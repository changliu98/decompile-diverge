int func0(struct matrix *m) {
    size_t n = m->size;
    double *a = (double *)malloc(n * n * sizeof(double));
    if (!a)
        return -1;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            a[i * n + j] = m->data[i * n + j];
    m->data = a;
    return 0;
}