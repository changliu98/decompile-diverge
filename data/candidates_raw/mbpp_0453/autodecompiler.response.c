int d(int n) {
    int sum;
    if(n % 2 != 0) {
        sum = 0;
    } else {
        int k, p, s, t, m, j;
        k = 1; p = 2; s = 1; t = 1;
        while(p <= (int)sqrt((double)n)+1) {
            m = 0; j = 1;
            while(n % p == 0) {
                m++;
                n /= p;
                if(p == 2 && m == 1) j = 0;
                j *= p;
                s += j;
            }
            k *= s;
            s = 1;
            j = 1;
            p++;
        }
        if(n >= 2) k *= (n+1);
        sum = k;
    }
    return sum;
}