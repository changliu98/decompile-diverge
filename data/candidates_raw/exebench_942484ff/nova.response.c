void func0(double a, double b, double c, double d, double *x1, double *x2) {
    *x1 = (-b * c + sqrt(b * b - 4 * a * d)) / (2 * a);
    *x2 = (-b * c - sqrt(b * b - 4 * a * d)) / (2 * a);
}