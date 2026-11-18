void rifft1pt(float *v, float t) {
    float x = v[0], y = v[1];
    float d = x + y;
    float dx = x - y;
    v[0] = t * d;
    v[1] = t * dx;
}