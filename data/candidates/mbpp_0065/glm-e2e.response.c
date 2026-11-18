int func0(int *arr, int n) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        if (arr[i] < 0) {
            int temp = -arr[i];
            sum += func0(arr + i + 1, temp);
            i += temp;
        } else {
            sum += arr[i];
        }
        i++;
    }
    return sum;
}