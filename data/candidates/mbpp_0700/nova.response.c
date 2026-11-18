int func0(int *arr, int n, int x, int y) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] >= x && arr[i] <= y)
            count++;
    }
    return count;
}