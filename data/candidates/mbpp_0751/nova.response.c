bool func0(int *arr, int n, int i) {
    bool left, right, root;
    if (i * 2 + 2 > n) {
        left = true;
    } else {
        left = func0(arr, n, i * 2 + 1);
    }
    if (i * 2 + 1 > n) {
        right = true;
    } else {
        right = func0(arr, n, i * 2 + 2);
    }
    if (left && right && arr[i] >= arr[i * 2 + 1] && arr[i] >= arr[i * 2 + 2]) {
        root = true;
    } else {
        root = false;
    }
    return root;
}