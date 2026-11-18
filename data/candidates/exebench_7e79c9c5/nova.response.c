float spline_cubic_val(int n, float x[], float t[], float x0, float y0[]) {
    int i = 0;
    int index = n - 2;
    float y1, y2, y3;
    while (i < n - 1) {
        if (x0 > x[i + 1])
            index = i;
        else
            i++;
    }
    y1 = y0[index];
    y2 = (x0 - x[index + 1]) / (x[index] - x[index + 1]) * y0[index + 1] +
         (x[index] - x0) / (x[index] - x[index + 1]) * y0[index + 1];
    y3 =
        (x0 - x[index + 1]) * (x0 - x[index + 1]) /
            ((x[index] - x[index + 1]) * (x[index] - x[index + 1])) * y0[index + 1] +
        (x[index] - x0) * (x[index] - x0) /
            ((x[index] - x[index + 1]) * (x[index] - x[index + 1])) * y0[index + 1];
    return y1 + y2 + y3;
}