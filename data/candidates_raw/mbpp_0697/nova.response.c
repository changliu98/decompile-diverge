int func0(int *arr, int n) {
    int i, j, count = 0;
    for (i = 0, j = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            count++;
        else
            j++;
    }
    return count;
}