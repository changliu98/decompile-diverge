void FindDivDiff5Coeff1(double x0, double x1, double x2, struct Coeffs *coeffs) {
    double h1 = 1.0 / (x1 - x0);
    double h2 = 1.0 / (x2 - x0);
    double h3 = 1.0 / (x2 - x1);

    coeffs->c1 = h1 * h1 * h2 * h2;
    coeffs->c0 = 2.0 * (h1 + h2) * coeffs->c1;

    coeffs->c3 = h3 * h3 * h1 * h1;
    coeffs->c2 = -2.0 * (h3 - h1) * coeffs->c3;

    coeffs->c5 = h3 * h3 * h2 * h2;
    coeffs->c4 = 4.0 * (h3 + h2) * coeffs->c5;
}