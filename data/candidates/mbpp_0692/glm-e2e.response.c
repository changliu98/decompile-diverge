int func0(int n) {
    int result;
    int product = 1;
    int i;

    if (n >= 10) {
        result = 0;
    } else {
        for (i = 1; i <= n; i++) {
            product = (product * i) % 100;
        }
        result = product;
    }

    return result;
}