void geom_matinv2d(double d[2][2]) {
    double det = d[0][0] * d[1][1] - d[0][1] * d[1][0];
    double tmp = d[0][0];
    d[0][0] = d[1][1] / det;
    d[0][1] = -d[0][1] / det;
    d[1][0] = -d[1][0] / det;
    d[1][1] = tmp / det;
}