void func0(double *v, int n, double *s) {
    int i;
    double soma = 0.0;
    for (i = 0; i < n; i++)
        soma += v[i];
    *s = soma;
}