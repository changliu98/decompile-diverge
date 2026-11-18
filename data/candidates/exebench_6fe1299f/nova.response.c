void quant_u(float *out, int *index, float a, float b, int n) {
    float *p = out;
    int i;
    float delta;
    int idx;

    delta = (b - a) / (n - 1);
    for (i = 0; i < n - 1; i++) {
        float x = a + delta * i;
        if (x > *p) {
            *(p++) = x;
            idx = i;
        }
    }
    *p = a + delta * idx; 
    *index = idx;
}