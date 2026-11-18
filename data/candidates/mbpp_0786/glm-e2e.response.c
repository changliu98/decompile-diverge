int func0(int *arr, int n, int x) {
    int i = 0;
    while (i < n) {
        if (arr[i] > x) {
            break;
        }
        i++;
    }
    return i;
}