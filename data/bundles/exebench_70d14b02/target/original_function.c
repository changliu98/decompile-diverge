void
lib3ds_vector_max(float c[3], float a[3]) {
    int i;
    for (i = 0; i < 3; ++i) {
        if (a[i] > c[i]) {
            c[i] = a[i];
        }
    }
}