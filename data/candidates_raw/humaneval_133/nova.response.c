int func0(float *v, int n) {
    int i, func0 = 0, ceil_v;
    for (i = 0; i < n; i++) {
        ceil_v = (int)ceil(v[i]);
        func0 += ceil_v * (int)ceil(v[i]);
    }
    return func0;
}