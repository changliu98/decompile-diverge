int func0(int n) {
    int sum, i;
    if (n % 2) {
        printf("3 + 5 +... + %d\n", n);
        sum = -1;
    } else {
        sum = 0;
        i = 0;
        while (n >= 3) {
            i++;
            sum += n;
            n -= 2;
        }
        sum /= i;
    }
    return sum;
}