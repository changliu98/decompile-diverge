int HPCC_factor235(int n, struct Factors *factors) {
    factors->factor5 = 0;
    factors->factor3 = 0;
    factors->factor2 = 0;

    if (n % 2 != 0 && n % 3 != 0 && n % 5 != 0) {
        return 1;
    }
    
    if (n <= 1) {
        return 1;
    }

    while (n > 1 && n % 2 == 0) {
        factors->factor2++;
        n /= 2;
    }

    while (n > 1 && n % 3 == 0) {
        factors->factor3++;
        n /= 3;
    }

    while (n > 1 && n % 5 == 0) {
        factors->factor5++;
        n /= 5;
    }

    if (n == 1) {
        return 0;
    }

    return 1;
}