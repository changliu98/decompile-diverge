int func0(int n) {
    int sum;
    if (n < 2)
        sum = 0;
    else
        sum = n + func0(n - 2);
    return sum;
}