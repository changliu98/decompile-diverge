void func0(float *out, float *v) {
    int i;
    for (i = 0; i < 4; i++) {
        out[i] = v[i] > 0.0f? v[i] : 0.0f;
    }
}