void get_vector_modulo(int *a, int *b) {
    int i;
    for (i = 0; i < 4; i++) {
        a[i] = a[i] % b[i];
        if (a[i] < b[i])
            a[i] += b[i];
    }
}