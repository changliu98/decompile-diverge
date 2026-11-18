int func0(int n) {
    int product = 1;
    int has_odd = 0;
    int result;
    int digit;

    while (n > 0) {
        digit = n % 10;
        if (digit % 2 == 1) {
            has_odd = 1;
            product *= digit;
        }
        n = n / 10;
    }

    if (has_odd != 0) {
        result = product;
    } else {
        result = 0;
    }

    return result;
}