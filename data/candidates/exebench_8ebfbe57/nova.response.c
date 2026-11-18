float spline_cubic_val(int n, float *x, float *y, float *z, float t) {
    int i = 0;
    int j = n - 2;
    float a, b, c, d, e, f, g;
    float h;
    while (i < n - 1) {
        if (x[i + 1] > t) {
            j = i;
            break;
        }
        i++;
    }
    a = x[j] - t;
    b = x[j + 1] - x[j];
    c = z[j] - z[j + 1];
    d = z[j] - y[j];
    e = y[j + 1] - y[j];
    f = y[j + 1] - t;
    g = b * d;
    h = b * e + f * g + c * d + a * e + f * d;
    h = h / (b * e);
    return h;
}