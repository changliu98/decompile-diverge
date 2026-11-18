void func0(float x, float y, float *a, float *b, float *c) {
    *a = (y * y - x * x) / 4.0f;
    *b = (2.0f * y * y + x * x) / 4.0f;
    *c = (y * y + x * x) / 4.0f;
}