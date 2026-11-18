void func0(int *arr, int n, int x) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    if (x > arr[n - 1]) {
        printf("%d", x);
    } else {
        printf("%d", arr[n - 1]);
    }
}