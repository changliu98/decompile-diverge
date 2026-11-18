double randlc(double *x, double a) {
    const double r23 = 0.5e0;          // 2^-1 (approx, actually 8388608.0 / 16777216.0)
    const double t23 = 8388608.0e0;    // 2^23
    const double t46 = 70368744177664.0e0; // 2^46
    const double r46 = 1.0e0 / 70368744177664.0e0; // 2^-46

    // Break down a into a1 (high 23 bits) and a2 (low 23 bits)
    double t1 = r23 * a;
    int i1 = (int)t1;
    double a1 = (double)i1;
    double a2 = a - a1 * t23;

    // Break down x into x1 (high 23 bits) and x2 (low 23 bits)
    double t2 = r23 * (*x);
    int i2 = (int)t2;
    double x1 = (double)i2;
    double x2 = (*x) - x1 * t23;

    // Perform the multiplication in parts
    double t3 = a1 * x2 + a2 * x1;
    int i3 = (int)(r23 * t3);
    double t4 = (double)i3;
    double t5 = t3 - t4 * t23;

    // Combine the parts and apply the modulo 2^46
    *x = a2 * x2 + t5 * t23;
    int i4 = (int)(r46 * (*x));
    double t6 = (double)i4;
    *x = *x - t6 * t46;

    // Scale the result to be between 0.0 and 1.0
    double result = r46 * (*x);
    return result;
}