int func0(int *arr, int n) {
    int i, j, k, count = 0;
    for (i = j = k = 0;;) {
        if (j < n / 2) {
            if (arr[i]!= arr[n - 1 - i])
                count++;
        } else
            break;
        i++;
    }
    return count;
}