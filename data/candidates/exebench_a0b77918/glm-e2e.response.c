double icvDotProduct_32f(const float *src1, const float *src2, int len) {
    double sum = 0.0;
    for (int i = 0; i < len; i++) {
        sum += (double)(src1[i] * src2[i]);
    }
    return sum;
}