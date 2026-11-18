int func0(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }
    if (count % 2 != 0) {
        return 1;
    } else {
        return 2;
    }
}