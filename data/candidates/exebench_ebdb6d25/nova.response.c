void swi_coortrf2(double x[3], double y[3], double t) {
    double xt = x[0] + t * x[1] + t * t * x[2];
    double yt = y[0] + t * y[1] + t * t * y[2];
    y[0] = xt;
    y[1] = yt;
    y[2] = t * y[1] + t * t * y[2];
}