void mat3mulv(float *output, float *in0, float *in1) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            output[i] += in0[i * 4 + j] * in1[j];
        }
    }
}