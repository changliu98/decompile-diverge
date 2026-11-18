int func0(int *arr, int n) {
    int i, j, k, l, m, temp;
    int flag;
    int ans;
    for (i = 1; i < n; i++) {
        for (j = i; j > 0; j--) {
            flag = (arr[j] > arr[j - 1])? 1 : 0;
            if (flag % 2 == 0)
                continue;
            else {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
    for (i = 0; i < n; i++) {
        if (i == 0 || arr[i]!= arr[i - 1]) {
            ans = arr[i] * m;
        } else {
            m = m * arr[i];
        }
    }
    return ans;
}