int func0(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int temp = i * 2;
        sum += temp * temp * temp * temp;
    }
    return sum;
}