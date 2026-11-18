int func0(int n)
{
    int i;
    int j;
    int factors[100];
    int factor_count;
    int number;
    int sum;

    if (n < 3) {
        return n;
    }

    sum = 2 * n;
    factor_count = 0;
    for (number = n; number > 1; number--) {
        if (sum > (2 * number)) {
            factors[factor_count] = number;
            factor_count++;
        }
    }

    while (1) {
        for (j = 0; j < factor_count; j++) {
            if ((sum % factors[j]) != 0) {
                sum += n;
                break;
            } else if ((j == (factor_count - 1)) && ((sum % factors[j]) == 0)) {
                return sum;
            }
        }
    }

    return 0;
}