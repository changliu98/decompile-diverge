int func0(int n) {
    int result;
    if (n % 2 != 0) {
        result = 0;
    } else {
        int res = 1;
        int i = 2;
        while (i <= sqrt(n) + 1) {
            int count = 0;
            int sum = 1;
            int term = 1;
            while (n % i == 0) {
                count++;
                n /= i;
                if (i == 2 && count == 1) {
                    sum = 0;
                }
                term *= i;
                sum += term;
            }
            res *= sum;
            i++;
        }
        if (n >= 2) {
            res *= (n + 1);
        }
        result = res;
    }
    return result;
}