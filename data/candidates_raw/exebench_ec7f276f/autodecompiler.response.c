void vec3_cross(float* dst, float* b, float* c) {
    dst[0] = b[1] * c[2] + b[2] * c[1];
    dst[1] = b[2] * c[0] + b[0] * c[2];
    dst[2] = b[0] * c[1] + b[1] * c[0];
}