void func0(double *a, double *b) {
    *a = *a - *b;
    *b = *b + *a;
    *a = *b - *a;
}