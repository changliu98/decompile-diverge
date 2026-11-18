void func0(int *arr, int n) {
    int last = -1;
    for (int i = 0; i < n; i++) {
        if (last >= 0) {
            if ((arr[i] < 0 && arr[last] < 0) || (arr[i] >= 0 && arr[last] >= 0)) {
                right_rotate(arr, n, last, i);
                if (i - last > 2) {
                    last = last + 2;
                } else {
                    last = -1;
                }
            }
        }
        if (last == -1) {
            if ((arr[i] >= 0 && i % 2 == 0) || (arr[i] < 0 && i % 2 == 1)) {
                last = i;
            }
        }
    }
}