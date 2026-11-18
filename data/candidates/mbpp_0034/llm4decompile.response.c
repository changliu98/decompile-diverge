int func0(int *ar, int N) {
    int l = 0, r = N - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (ar[mid] == mid + 1 || ar[mid - 1] == mid) return -1;
        if (ar[mid] == mid + 1) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}