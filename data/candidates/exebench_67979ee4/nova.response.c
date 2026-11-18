void quaternionComposition(float x1, float y1, float x2, float y2, float x3, float y3,
             float *x4, float *y4) {
    *x4 = x1 * x3 * (1 - y1) + x2 * x1 * (1 - y3) + x3 * x2 * (1 - y1);
    *y4 = y1 * x3 * (1 - x1) + y2 * x1 * (1 - y3) + y3 * x2 * (1 - x1);
}