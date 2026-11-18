void func0(float *output, float *in0, float s, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = in0[i] * s;
    }
}