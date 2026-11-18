int func0(int n, int a, int b) {
    int is_prime = 1;
    int i;
    int result;

    if (n < 2) {
        is_prime = 0;
    }

    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            is_prime = 0;
        }
    }

    if (is_prime != 0) {
        result = a;
    } else {
        result = b;
    }

    return result;
}