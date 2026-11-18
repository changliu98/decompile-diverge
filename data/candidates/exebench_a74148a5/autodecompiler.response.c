float getUniform(float a, float b, int c, float *d) {
    float e = (*d * a) + b;
    int f = e / c;
    e = e - (f * c);
    *d = e / c;
    return *d;
}