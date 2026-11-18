int func0(float f, float *r) {
    r[3] = f;
    if (f < 0) {
        r[0] = 0;
        r[1] = -INFINITY;
        if (f == -INFINITY) {
            r[2] = 0;
            r[3] = -INFINITY;
        }
    } else {
        r[0] = -INFINITY;
        r[1] = f;
        r[2] = f;
        r[3] = f;
    }
    return 0;
}