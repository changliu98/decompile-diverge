void lib3ds_quat_copy(float *out, float *in) {
    int i;
    for (i = 0; i < 5; i++) {
        out[i] = in[i];
    }
}