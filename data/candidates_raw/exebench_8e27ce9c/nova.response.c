static void func0(float *x, float *y) {
    float t = *x + *y;
    *y = *x - *y;
    *x = t;
}