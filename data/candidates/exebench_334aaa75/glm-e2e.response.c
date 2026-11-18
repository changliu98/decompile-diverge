void phi2D_lin(double x, double y, double phi[4]) {
    phi[0] = (1.0 - x) * (1.0 - y);
    phi[1] = x * (1.0 - y);
    phi[2] = x * y;
    phi[3] = (1.0 - x) * y;
}