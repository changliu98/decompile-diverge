void func0(float *v) {
    float x = v[0];
    float y = v[1];
    float z = x + y;
    float w = x - y;
    v[0] = z;
    v[1] = w;
}