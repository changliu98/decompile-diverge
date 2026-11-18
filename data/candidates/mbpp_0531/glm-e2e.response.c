int func0(int *arr, int n, int target) {
    if (target == 0) {
        return 0;
    }

    int min_coins = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] <= target) {
            int res = func0(arr, n, target - arr[i]);
            if (res != INT_MAX && res + 1 < min_coins) {
                min_coins = res + 1;
            }
        }
    }

    return min_coins;
}