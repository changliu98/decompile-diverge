void func0(float x, float y, float z, int t, float *x2, float *y2) {
    float a = (x - 2 * y + z) / (2 * z + x - y);
    *x2 = a * cos(alpha);
    *y2 = z - x + a * sin(alpha);
}