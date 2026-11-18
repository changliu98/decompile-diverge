int func0(unsigned int n, int *p, int *q) {
    int a = 0, b = 0, c = 0;
    if (n == 0)
        c = 0;
    else {
        if (p!= NULL)
            *p = 0;
        if (q!= NULL)
            *q = 0;
        while (n > 0) {
            if (n % 2 == 1) {
                b++;
                if (b == 1) {
                    if (p!= NULL)
                        *p = a;
                } else if (b == 2) {
                    if (q!= NULL)
                        *q = a;
                } else {
                    c = 0;
                    break;
                }
            }
            a++;
            n = n / 2;
        }
        c = 1;
    }
    return c;
}