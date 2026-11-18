int func0(int limit)
{
    int amicables_sum = 0;
    int sum = 0;
    int i;
    if (limit < 2) {
        i = -1;
    } else {
        for (i = 2; i <= limit; i++) {
            int sum1 = 0;
            int j;
            for (j = 1; j < i; j++) {
                if (i % j == 0) {
                    sum1 += j;
                }
            }

            int sum2 = 0;
            int k;
            for (k = 1; k < sum1; k++) {
                if (sum1 % k == 0) {
                    sum2 += k;
                }
            }

            if (i == sum2 && i != sum1) {
                amicables_sum += i;
            }
        }
        i = amicables_sum;
    }
    return i;
}