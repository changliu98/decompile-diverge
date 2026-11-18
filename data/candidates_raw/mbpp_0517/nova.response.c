int func0(int *arr, int n) {
    int max = arr[0];
    int i = 0;
    while (i < n) {
        if (arr[i] > max)
            max = arr[i];
        else
            i++;
    }
    return max;
}