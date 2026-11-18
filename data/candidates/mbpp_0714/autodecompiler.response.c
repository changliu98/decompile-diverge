int func0(int n) {
    int limit = n;
    int numberOfDivisors = 0;
    int divisor = 2;

    while (1) {
        if (divisor * divisor > limit)
            break;

        int exponent = 0;
        while (n % divisor == 0) {
            n /= divisor;
            ++exponent;
        }

        int temp = 0;
        int power = 1;
        while (1) {
            if (temp + power > exponent)
                break;

            temp += power;
            ++numberOfDivisors;
            power++;
        }

        ++divisor;
    }

    if (n != 1)
        ++numberOfDivisors;

    return numberOfDivisors;
}