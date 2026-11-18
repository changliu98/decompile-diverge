void mlVectorScaleTo(float *in, float scale, float *out) {
    for (int i = 0; i < 3; i++) {
        out[i] = in[i] * scale;
    }
}