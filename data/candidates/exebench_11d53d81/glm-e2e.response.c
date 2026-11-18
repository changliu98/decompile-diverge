void eeval(double x, double a, double b, double c, double d, double *out1, double *out2, double *out3, double *out4) {
    double term1 = a * x;
    double term2 = term1 + b;
    double term3 = term2 * x + c;
    double term4 = (term1 + term2) * x + term3;
    double term5 = term3 * x + d;

    *out1 = term5;
    *out2 = term4;
    *out3 = term2;
    *out4 = term3;
}