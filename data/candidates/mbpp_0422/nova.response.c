double func0(int n) {
    double sum = 0;
    int sign = 1;
    for (int i = a; i <= n; i++) {
        sum += sign * 1.0 / (i * i * i);
        sign = -sign;
    }
    return roundl(sum / n * 1000) / 1000.0;
}