int get_prime_factors(int n, int *factors) {
    int i, j, k, m;
    int num;
    int index = 0;

    num = n;

    while (num % 53 == 0) {
        num /= 53;
        factors[index] = 53;
        index++;
    }
    while (num % 47 == 0) {
        num /= 47;
        factors[index] = 47;
        index++;
    }
    while (num % 43 == 0) {
        num /= 43;
        factors[index] = 43;
        index++;
    }
    while (num % 41 == 0) {
        num /= 41;
        factors[index] = 41;
        index++;
    }
    while (num % 37 == 0) {
        num /= 37;
        factors[index] = 37;
        index++;
    }
    while (num % 31 == 0) {
        num /= 31;
        factors[index] = 31;
        index++;
    }
    while (num % 29 == 0) {
        num /= 29;
        factors[index] = 29;
        index++;
    }
    while (num % 23 == 0) {
        num /= 23;
        factors[index] = 23;
        index++;
    }
    while (num % 19 == 0) {
        num /= 19;
        factors[index] = 19;
        index++;
    }
    while (num % 17 == 0) {
        num /= 17;
        factors[index] = 17;
        index++;
    }
    while (num % 13 == 0) {
        num /= 13;
        factors[index] = 13;
        index++;
    }
    while (num % 11 == 0) {
        num /= 11;
        factors[index] = 11;
        index++;
    }
    while (num % 8 == 0) {
        num /= 8;
        factors[index] = 8;
        index++;
    }
    while (num % 7 == 0) {
        num /= 7;
        factors[index] = 7;
        index++;
    }
    while (num % 5 == 0) {
        num /= 5;
        factors[index] = 5;
        index++;
    }
    while (num % 4 == 0) {
        num /= 4;
        factors[index] = 4;
        index++;
    }
    while (num % 3 == 0) {
        num /= 3;
        factors[index] = 3;
        index++;
    }
    while (num % 2 == 0) {
        num /= 2;
        factors[index] = 2;
        index++;
    }

    if (num < 32) return index;

    for (i = 2; i < num; i++) {
        m = 6 * i - 1;
        k = 6 * i + 1;
        while (num % m == 0) {
            factors[index] = m;
            index++;
            num /= m;
        }
        while (num % k == 0) {
            factors[index] = k;
            index++;
            num /= k;
        }
    }

    return index;
}