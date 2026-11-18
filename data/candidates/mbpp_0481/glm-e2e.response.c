bool func0(int *arr, int n, int target) {
    if (target == 0) {
        return true;
    }
    if (n == 0) {
        return false;
    }
    
    if (arr[n - 1] > target) {
        return func0(arr, n - 1, target);
    } else {
        bool without_last = func0(arr, n - 1, target);
        if (!without_last) {
            return func0(arr, n - 1, target - arr[n - 1]);
        }
        return true;
    }
}