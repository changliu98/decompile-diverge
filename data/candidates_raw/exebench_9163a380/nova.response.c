void func0(float x, float y, float z, float *a, float *b, float *c) {
    float a1, b1, c1;
    int i;
    for (i = 0; i < 6; i++) {
        if (z == 0) {
            a1 = 0;
            b1 = 0;
            c1 = 0;
        } else if (y == 0) {
            a1 = z;
            b1 = z;
            c1 = z;
        } else if (i == 1) {
            a1 = z;
            b1 = z;
            c1 = z;
        } else if (i == 2) {
            a1 = z;
            b1 = z;
            c1 = z;
        } else if (i == 3) {
            a1 = z;
            b1 = z;
            c1 = z;
        } else if (i == 4) {
            a1 = z;
            b1 = z;
            c1 = z;
        } else if (i == 5) {
            a1 = z;
            b1 = z;
            c1 = z;
        }
    }
    *a = a1;
    *b = b1;
    *c = c1;
}