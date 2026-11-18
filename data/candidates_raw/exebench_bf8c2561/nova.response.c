double func0(double f[], size_t length) {
    size_t i;
    size_t N = length / sizeof(double);
    double summe = 0;

    for (i = 0; i < N; i++) {
        summe += f[i];
    }
    f[0] = summe / (N - 1);
    return summe;
}