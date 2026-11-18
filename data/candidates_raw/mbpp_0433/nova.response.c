void func0(int *arr, int n, int x) {
    int i = 0, j, temp;
    while (i < n - 1) {
        j = 0;
        while (j < n - i - 1) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    if (x > arr[n - 1]) {
        printf("The number is greater than the largest element in the array");
    } else {
        printf("The number is present in the array");
    }
}