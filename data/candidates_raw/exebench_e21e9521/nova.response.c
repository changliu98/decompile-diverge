float func0(float *a, float *b, size_t len) {
    float ret = 0;
    for (size_t i = 0; i < len; i++)
        ret += a[i] * b[i];
    ret /= len;
    return ret;
}