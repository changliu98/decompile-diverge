float func0(float *p, float x, float y, int n) {
    float x1, x2, y1, y2, z, t;
    int i;
    do {
        if (x == -1.0)
            x1 = -1.0;
        else if (x == 1.0)
            x1 = 1.0;
        else
            x1 = x;
        if (y == -1.0)
            y1 = -1.0;
        else if (y == 1.0)
            y1 = 1.0;
        else
            y1 = y;
        x2 = x1;
        y2 = y1;
        for (i = 0; i < n; i++) {
            x1 = x2;
            y1 = y2;
            x2 = x1 + (y1 - x1) * (x1 - y1) * (1 - x1);
            y2 = y1 + (x1 - y1) * (x1 - y1) * (1 - y1);
        }
        z = x2;
        t = y2;
    } while (x2!= x1 || y2!= y1);
    z = x1 + (y1 - x1) * (y1 - x1) * (z - x1);
    return z;
}