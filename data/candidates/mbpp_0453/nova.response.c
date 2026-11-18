int func0(int n) {
    int i, j, k, l, m, p, q, r, s, t, ans;
    if (n % 2!= 0)
        ans = 0;
    else {
        ans = 1;
        for (i = 2; i <= (int)sqrt(n) + 1; i++) {
            k = 0;
            for (j = 1;; j++) {
                if (n % i == 0) {
                    k++;
                    n /= i;
                    if (i == 2 && j == 1) {
                        p = 0;
                        q = i * j;
                        p += q;
                    }
                } else {
                    ans *= k;
                    i++;
                }
            }
        }
        if (n >= 3)
            ans *= (n + 1);
    }
    return ans;
}