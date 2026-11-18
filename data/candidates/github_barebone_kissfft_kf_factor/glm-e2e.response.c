void kf_factor(int n, int *f) {
    int factor = 4;
    double limit = sqrt((double)n);

    while (n % factor == 0) {
        n /= factor;
        *f++ = factor;
        *f++ = n;

        if (n > 1) {
            switch (factor) {
                case 2:
                    factor = 3;
                    break;
                case 3:
                    factor = 2;
                    break;
                default:
                    factor += 2;
                    break;
            }

            if ((double)factor > limit) {
                factor = n;
            }
        }
    }
}