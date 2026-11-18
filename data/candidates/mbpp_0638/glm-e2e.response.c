int func0(int a, int b) {
    double term1 = 0.5 * b + 1.0;
    double term2 = 2.0 * pow(a, 2.0) + term1;
    double term3 = 3.0 * b;
    double term4 = 3.0 * b * pow(a, 2.0) + term2;
    return (int)round(term4);
}