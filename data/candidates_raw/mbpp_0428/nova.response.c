void func0(int *arr, int n) {
    int gap = n / 2;
    while (gap > 0) {
        int i, j;
        for (i = gap; i < n; i++) {
            int tmp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > tmp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = tmp;
        }
        gap /= 2;
    }
}