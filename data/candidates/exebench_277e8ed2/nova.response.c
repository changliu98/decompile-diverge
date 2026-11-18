void calc_sth11(float *x, float *y) {
    float x1 = -1.0f, x2 = 1.0f;
    float y1 = -1.4f, y2 = 1.4f;
    float x0 = (*x);
    float y0 = (*y);
    float xy = (x0 * x0 * x0 - 3 * x0 * x0 + 3 * x0) * (y0 * y0) +
               (x0 * x0 - 2 * x0) * (y0 * y0 * y0 - 3 * y0 * y0 + 3 * y0);
    float yy = (y0 * y0 * y0 - 3 * y0 * y0 + 3 * y0) * (x0 * x0) +
               (y0 * y0 - 2 * y0) * (x0 * x0 * x0 - 3 * x0 * x0 + 3 * x0);
    if (yy > y2)
        yy = y2;
    if (yy < y1)
        yy = y1;
    (*x) = xy;
    (*y) = yy;
}