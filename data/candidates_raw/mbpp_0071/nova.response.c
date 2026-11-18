void func0(int *arr, int arr_len) {
    float k = 1.247f;
    int step = arr_len;
    int i = 0;
    bool swapped = true;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= k;
        swapped = false;
        for (i = 0; i + step < arr_len; ++i) {
            if (arr[i] > arr[i + step]) {
                int tmp = arr[i];
                arr[i] = arr[i + step];
                arr[i + step] = tmp;
                swapped = true;
            }
        }
    }
}