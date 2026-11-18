int func0(int *arr, int n) {
    int max = INT_MAX;
    int i = 0;
    while (i < n) {
        if (arr[i] < max)
            max = arr[i];
        i++;
    }
    return max;
}