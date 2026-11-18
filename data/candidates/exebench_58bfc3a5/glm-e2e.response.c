void FindDivDiff4Coeff(double x0, double x1, double x2, double x3, double x4, double *coeffs) {
    coeffs[0] = 1.0 / ((x0 - x1) * (x0 - x2) * (x0 - x3) * (x0 - x4));
    coeffs[1] = 1.0 / ((x1 - x0) * (x1 - x2) * (x1 - x3) * (x1 - x4));
    coeffs[2] = 1.0 / ((x2 - x0) * (x2 - x1) * (x2 - x3) * (x2 - x4));
    coeffs[3] = 1.0 / ((x3 - x0) * (x3 - x1) * (x3 - x2) * (x3 - x4));
    coeffs[4] = 1.0 / ((x4 - x0) * (x4 - x1) * (x4 - x2) * (x4 - x3));
}