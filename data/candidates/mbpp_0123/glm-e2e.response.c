int func0(int n) {
    int res;
    int count;
    int i;
    int sum_div;
    int j;
    int sum_div2;
    int k;

    if (n < 1) {
        res = -1;
    } else {
        count = 0;
        for (i = 2; i <= n; i++) {
            sum_div = 0;
            for (j = 1; j < i; j++) {
                if (i % j == 0) {
                    sum_div += j;
                }
            }
            
            sum_div2 = 0;
            for (k = 1; k < sum_div; k++) {
                if (sum_div % k == 0) {
                    sum_div2 += k;
                }
            }
            
            if (i == sum_div2 && i != sum_div) {
                count += i;
            }
        }
        res = count;
    }
    
    return res;
}