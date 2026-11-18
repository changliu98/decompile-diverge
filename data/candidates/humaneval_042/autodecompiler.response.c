void func0(int *arr, int n) {
    int i = 0;
    while (1) {
        if (i < n) {
            arr[i] += 1;
            i++;
        } else {
            return;
        }
    }
}