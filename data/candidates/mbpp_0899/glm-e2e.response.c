bool func0(int *arr, int n) {
    int state = 0;
    for (int i = 1; i < n; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff > 0 && state == 1) {
            return false;
        }
        if (diff < 0) {
            state = 1;
        }
    }
    return true;
}