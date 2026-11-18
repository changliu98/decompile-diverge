int stb_div_eucl(int a, int b) {
    int q;
    int r;
    int rem;

    if (a >= 0) {
        if (b >= 0) {
            q = a / b;
        } else {
            if (b == -2147483648) {
                r = 0;
                rem = a;
            } else {
                r = -(a / -b);
                rem = a % -b;
            }
            q = r;
        }
    } else {
        if (a == -2147483648) {
            if (b >= 0) {
                r = -((-(a + b)) / b) - 1;
                rem = -((-(a + b)) % b);
                q = r;
            } else {
                if (b == -2147483648) {
                    r = 1;
                    rem = 0;
                } else {
                    r = (-(a - b)) / -b + 1;
                    rem = -((-(a - b)) % -b);
                }
                q = r;
            }
        } else {
            if (b >= 0) {
                r = -((-a) / b);
                rem = -((-a) % b);
                q = r;
            } else {
                if (b == -2147483648) {
                    r = 1;
                    rem = a - r * b;
                } else {
                    r = (-a) / -b;
                    rem = -((-a) % -b);
                }
                q = r;
            }
        }
    }

    if (rem < 0) {
        int adj = (b > 0) ? -1 : 1;
        q += adj;
    }

    return q;
}