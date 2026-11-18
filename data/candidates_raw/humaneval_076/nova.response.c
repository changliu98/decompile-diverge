int func0(int n, int m) {
    int i, j, k, l, p, q, r, s, t, x, y, z;
    int ans;

    i = 1;
    k = 0;
    while (1) {
        if (i > n) {
            ans = k < 100;
            break;
        }
        if (k % 2 == 0) {
            if (i == n) {
                ans = 1;
                break;
            }
            i *= m;
            k++;
        } else {
            ans = 0;
            break;
        }
    }

    return ans;
}