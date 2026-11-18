char *func0(int *arr, int n, int k) {
    int i, sum = 0;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    char *ans;
    if (k == 1) {
        if (sum % 2 == 0)
            ans = "even";
        else
            ans = "odd";
    } else {
        ans = "odd";
    }
    return ans;
}