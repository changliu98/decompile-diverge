int func0(long long int a, long long int b) {
    long long int sum = a + b;
    int count = 0;
    while (sum > 0) {
        sum = sum / 10;
        count++;
    }
    return count;
}