int func0(int *arr, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2!= 0) {
            count++;
        } else {
            continue;
        }
    }
    return count;
}