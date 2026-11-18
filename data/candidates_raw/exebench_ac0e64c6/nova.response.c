void func0(float *output, float *in0, float *in1, float f) {
    for (int i = 0; i < 16; i++) {
        output[i] = in0[i] + in1[i] * f;
    }
}