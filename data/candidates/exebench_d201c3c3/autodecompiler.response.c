void vec4f_set(float* dst, float left, float right, float bottom, float top) {
    float lr = 1 / (left - right);
    float bt = 1 / (bottom - top);

    dst[0] = -2 * lr;
    dst[1] = 0;
    dst[2] = 0;
    dst[3] = 0;
    dst[4] = 0;
    dst[5] = -2 * bt;
    dst[6] = 0;
    dst[7] = 0;
    dst[8] = 0;
    dst[9] = 0;
    dst[10] = -1;
    dst[11] = 0;
    dst[12] = (left + right) * lr;
    dst[13] = (top + bottom) * bt;
    dst[14] = 0;
    dst[15] = 1;
}