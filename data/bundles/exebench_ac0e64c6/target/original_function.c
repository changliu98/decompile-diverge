void warp_mat4_add_scaled(float *out, const float *a, const float *b, float c) {
    for (int i = 0; i < 16; i++) {
        out[i] = a[i] + b[i] * c;
    }
}