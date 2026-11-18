int func0(int *arr1, int *arr2, int n) {
    int total = 0;
    int i;

    sort(arr1, n);
    sort(arr2, n);

    for (i = 0; i < n; i++) {
        total += abs(arr1[i] - arr2[i]);
    }

    return total;
}