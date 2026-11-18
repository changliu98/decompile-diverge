void func0(int *arr1, int *arr2, int *arr3, int n) {
    for (int i = 0; i < n; i++) {
        arr3[i] = abs(arr1[i] - arr2[i]);
    }
}