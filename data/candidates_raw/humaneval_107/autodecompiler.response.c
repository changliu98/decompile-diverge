int* dcount(int n) {
    int* res = malloc(2 * sizeof *res);
    res[0] = 0;
    res[1] = 0;

    for (int i = 1; ; ++i) {
        if (i > n) {
            break;
        }

        int r = 0;
        int x = i;
        int y = i;

        while (x != 0) {
            r = r * 10 + x % 10;
            x /= 10;
        }

        if (y == r) {
            if (y % 2 == 0) {
                res[0]++;
            } else {
                res[1]++;
            }
        }
    }

    return res;
}