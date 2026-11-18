void shape_tria6(double *in, double *out) {
    double x = in[0];
    double y = in[1];
    double z = 1.0 - x - y;
    
    out[0] = x * (2.0 * x - 1.0);
    out[1] = 4.0 * x * y;
    out[2] = y * (2.0 * y - 1.0);
    out[3] = 4.0 * y * z;
    out[4] = z * (2.0 * z - 1.0);
    out[5] = 4.0 * x * z;
}