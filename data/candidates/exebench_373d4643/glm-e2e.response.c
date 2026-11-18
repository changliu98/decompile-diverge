void lib3ds_vector_copy(float *dest, const float *src) {
    for (int i = 0; i < 3; i++) {
        dest[i] = src[i];
    }
}