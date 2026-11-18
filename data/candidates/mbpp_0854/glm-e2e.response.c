void func0(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        int j = 2 * i + 1;
        while (j < n) {
            if (j + 1 < n && arr[j] > arr[j + 1]) {
                j++;
            }
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                
                i = j - 1;
                j = 2 * j + 1;
            } else {
                break;
            }
        }
    }
}