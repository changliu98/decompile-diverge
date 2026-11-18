int func0(int n) {
    int sum = 0;
    for (int i = 1; n / i > 0; i *= 2) {
        sum += n / i;
    }
    return sum;
}