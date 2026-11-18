void rfft1pt(float *v) {
    float x = v[0];
    float y = v[1];
    float x1 = x + y;
    float y1 = x - y;
    v[0] = x1;
    v[1] = y1;
}