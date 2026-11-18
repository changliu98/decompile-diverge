void lib3ds_vector_max(float *a, float *b) {
    for (int i = 0; i < 3; i++) {
        if (b[i] > a[i]) {
            a[i] = b[i];
        }
    }
}