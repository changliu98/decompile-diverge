int func0(int *arr, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] == -1)
            break;
        else
            count++;
    }
    return count;
}