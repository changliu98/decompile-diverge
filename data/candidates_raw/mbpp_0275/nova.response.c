int func0(int *arr, int n, int k) {
    int i = 0;
    int max = -1;
    int index = -1;
    while (i < n) {
        arr[i] = (arr[i] / k) + (arr[i] % k!= 0);
        i++;
    }
    i = n - 1;
    while (i >= 0) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
        }
        i--;
    }
    return index + 1;
}