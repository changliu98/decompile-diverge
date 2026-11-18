void func0(float *x, float t, float dt) {
    long i = 0;
    while (1) {
        if (i >= 7)
            return;
        x[0] += (x[1] + x[2] - x[3]) * t;
        x[1] += (x[0] + x[2] - x[3]) * t;
        x[2] += (x[0] + x[1] - x[3]) * t;
        x[3] += (x[0] + x[1] + x[2]) * t;
        x[3] /= dt;
        i++;
    }
}