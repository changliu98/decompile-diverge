int func0(int *arr, int n) {
    int max = arr[0], min = arr[0], i = 1;
    while (1) {
        if (i >= n)
            break;
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
        i++;
    }
    return max - min;
}