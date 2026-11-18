void func0(int *arr1, int n, int *arr2) {
    for (int i = 0; i < n; i++) {
        arr2[i] = ~arr1[i];
    }
}