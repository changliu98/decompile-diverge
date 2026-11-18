int func0(int *arr, int n) {
    int l = 0, r = n - 1, m, lm, rm;
    while (l <= r) {
        if (arr[l] <= arr[r]) {
            m = l;
            break;
        }
        m = (l + r) / 2;
        lm = (m - 1 + n) % n;
        rm = (m + 1) % n;
        if (arr[lm] <= arr[m] && arr[rm] <= arr[m]) {
            m = m;
            break;
        } else if (arr[m] <= arr[r]) {
            r = m - 1;
        } else if (arr[l] <= arr[m]) {
            l = m + 1;
        }
    }
    return m;
}