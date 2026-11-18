int func0(int *arr, int x, int n) {
    int low = 0, high = n - 1;
    int res = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (x < arr[mid]) {
            high = mid - 1;
        } else if (x > arr[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
            res = mid;
        }
    }
    return res;
}