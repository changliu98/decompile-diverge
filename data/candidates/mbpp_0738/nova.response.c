double func0(int n) {
    double sum;
    if (n <= 0)
        sum = 0;
    else
        sum = (1 / pow(2, n)) + func0(n - 1);
    return sum;
}