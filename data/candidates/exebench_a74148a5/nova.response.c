float getUniform(int a, int b, int c, float *f) {
    float sum = a * (*f) + b;
    int d = sum / c;
    sum = sum - d * c;
    (*f) = sum / c;
    return sum;
}