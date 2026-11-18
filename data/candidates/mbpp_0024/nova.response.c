int func0(int n) {
    int temp = n;
    int sum = 0;
    int count = 0;
    while (n) {
        int rem = n % 10;
        int pow = powe(2, rem);
        sum = sum + (rem * pow);
        n = n / 10;
        count++;
    }
    return sum;
}