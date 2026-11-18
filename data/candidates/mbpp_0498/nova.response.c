int func0(int a, int b) {
    int i, j, k, l, m, n, x, y;
    int res = 1;

    if (a % b == 0) {
        res = b;
    } else {
        for (i = b / 2; i > 0; i--) {
            if (a % i == 0 && b % i == 0) {
                res = i;
                break;
            }
        }
    }
    return res;
}