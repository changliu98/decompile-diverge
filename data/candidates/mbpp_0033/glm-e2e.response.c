int func0(int n) {
    int sum = 0;
    int i = 0;
    while (n != 0) {
        int rem = n % 2;
        int pow10 = 1;
        for (int j = 0; j < i; j++) {
            pow10 *= 10;
        }
        sum += rem * pow10;
        n = n / 2;
        i++;
    }
    return sum;
}