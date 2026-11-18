void func0(float *out, float x, float y, float z) {
    float a = (float)M_PI * y;
    float s = (float)sin(a);
    float c = (float)cos(a);

    out[0] = x + (c * z);
    out[1] = s;
    out[2] = x - (c * z);
}