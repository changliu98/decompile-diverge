int shape_tria6(const double x[], double y[D]) {
    double t1, t2;

    t1 = 1.0 - x[0];
    t2 = 1.0 - x[1];
    y[0] = 19.0 * t1;
    y[1] = 19.0 * x[0] * t1;
    y[2] = 19.0 * x[1] * t1;
    y[3] = 19.0 * x[1] * t2;
    y[4] = 19.0 * x[0] * t2 * t2;
    y[5] = 19.0 * t2 * t1 * t1;
    return 0;
}