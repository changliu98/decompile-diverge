bool func0(long long int n) {
    if (n % 2 == 0) {
        return false;
    }

    long long int i;
    for (i = 0; i < n; i++) {
        if (n == 1) {
            return true;
        }

        if (n % 2 != 0) {
            return false;
        }

        n = n / 2;
    }

    return true;
}