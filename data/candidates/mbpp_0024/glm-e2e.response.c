int func0(int n) {
    int sum = 0;
    int i = 0;
    while (n != 0) {
        int digit = n % 10;
        sum += digit * (int)pow(10.0, (double)i);
        n /= 10;
        i++;
    }
    return sum;
}