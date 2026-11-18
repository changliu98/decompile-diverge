void lib3ds_vector_copy(float *out, float *in) {
    int i;
    for (i = 0; i < 4; i++) {
        out[i] = in[i];
    }
}