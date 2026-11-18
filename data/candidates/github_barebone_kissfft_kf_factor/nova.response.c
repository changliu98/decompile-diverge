void kf_factor(int n, int *p) {
    int i = 4;
    double d;
    do {
        d = sqrt(n);
        while (n % i!= 0) {
            switch (i) {
            case 2:
                i = 3;
                break;
            case 3:
                i = 2;
                break;
            default:
                i += 2;
            }
            if (i > d)
                i = n;
        }
        n /= i;
        *p++ = i;
    } while (n > 1);
}