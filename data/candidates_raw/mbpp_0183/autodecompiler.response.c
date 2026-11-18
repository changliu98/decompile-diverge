int pairs(int *a, int n, int k) {

    int ans = 0;
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] - a[j] == k || a[j] - a[i] == k) {
                ans++;
            }
        }
    }

    return ans;
}