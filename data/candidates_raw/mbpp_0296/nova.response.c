int func0(int *arr, int n) {
    int i, j, count = 0;
    for (i = 0;; i++) {
        for (j = i + 1;; j++) {
            if (j >= n) {
                i = 0;
                break;
            }
            if (arr[i] > arr[j])
                count++;
        }
    }
    return count;
}