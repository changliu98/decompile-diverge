int func0(int n) {
    int has_odd = 0;
    int prod = 1;
    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 1) {
            has_odd = 1;
            prod *= digit;
        }
        n /= 10;
    }
    if (has_odd) {
        return prod;
    } else {
        return 0;
    }
}