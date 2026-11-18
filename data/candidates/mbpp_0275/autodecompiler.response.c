int func0(int *arr, int n, int k) {
    int i = 0;
    while (1) {
        if (i < n) {
            arr[i] = arr[i]/k + (arr[i]%k != 0 ? 1 : 0);
            i++;
        } else {
            int max = -1, index = -1;
            for (i = n-1; i >= 0; i--) {
                if (arr[i] > max) {
                    max = arr[i];
                    index = i;
                }
            }
            return index + 1;
        }
    }
}