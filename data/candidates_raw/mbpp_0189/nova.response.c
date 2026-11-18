int func0(int *arr, int n) {
    int i, j, k, l, m, flag = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] == 1) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        int ans = 1;
        for (i = 0; i < n; i++) {
            if (arr[i] > 0 && arr[i] <= n) {
                arr[i] = 1;
            }
        }
        for (i = 0; i < n; i++) {
            j = i;
            while (arr[j] <= n) {
                arr[j] = arr[j] + arr[j - 1] % n;
                j++;
            }
            ans = j;
        }
        for (i = 0; i < n; i++) {
            if (arr[i] <= n) {
                ans = i + 1;
                break;
            }
        }
        ans = i + 1;
    }
    return ans;
}