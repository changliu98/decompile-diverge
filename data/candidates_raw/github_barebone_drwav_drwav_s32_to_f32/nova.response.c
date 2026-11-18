void func0(float *out, int *x, size_t len) {
    size_t i;

    if (!out ||!x) {
        return;
    }

    for (i = 0; i < len; i++) {
        out[i] = (float)(x[i] / 8388608.0); 
    }
}