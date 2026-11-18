void func0(int *arr, int n) {
    int step = n / 2;
    while (step > 0) {
        for (int i = step; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (1) {
                int condition = 0;
                if (j < step) {
                    condition = 1;
                } else if (arr[j - step] > temp) {
                    condition = 1;
                }
                
                if (condition) {
                    arr[j] = arr[j - step];
                    j = j - step;
                } else {
                    break;
                }
            }
            arr[j] = temp;
        }
        step = step / 2;
    }
}