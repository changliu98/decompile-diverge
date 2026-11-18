void func0(int *arr, int n) {
    int left = 0;
    int right = n - 1;
    int i = 0;
    
    while (i <= right) {
        if (arr[i] == 0) {
            int temp = arr[left];
            arr[left] = arr[i];
            arr[i] = temp;
            left++;
            i++;
        } else if (arr[i] == 1) {
            i++;
        } else {
            int temp = arr[i];
            arr[i] = arr[right];
            arr[right] = temp;
            right--;
        }
    }
}