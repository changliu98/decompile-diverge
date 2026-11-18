void FindDivDiff5Coeff2(double x0, double x1, double x2, double x3, double *coeffs) {
    // The constant 1.0 is loaded from memory at 0x2010
    double h1 = 1.0 / (x1 - x0);
    double h2 = 1.0 / (x2 - x0);
    double h3 = 1.0 / (x2 - x1);
    double h4 = 1.0 / (x3 - x0);
    double h5 = 1.0 / (x3 - x1);
    double h6 = 1.0 / (x3 - x2);

    // coeffs[0]
    coeffs[0] = -h1 * h1 * h2 * h2 * h4;

    // coeffs[1]
    coeffs[1] = -(2.0 * h3 + h5 - h1) * h1 * h5 * h3 * h3;

    // coeffs[2]
    coeffs[2] = -h1 * h5 * h3 * h3;

    // coeffs[3]
    coeffs[3] = -(h6 - 2.0 * h3 - h2) * h6 * h2 * h3 * h3;

    // coeffs[4]
    coeffs[4] = -h6 * h2 * h3 * h3;

    // coeffs[5]
    coeffs[5] = h4 * h5 * h5 * h6 * h6;
}