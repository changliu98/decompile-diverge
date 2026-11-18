void func0(int *arr, int n) {
    float gap = 1.3f;
    int gap_int = n;
    int swapped = 1;
    int i;

    while (gap_int > 1 || swapped != 0) {
        gap_int = (int)(gap_int / gap);
        swapped = 0;
        for (i = 0; gap_int + i < n; i++) {
            if (arr[i] > arr[i + gap_int]) {
                int temp = arr[i];
                arr[i] = arr[i + gap_int];
                arr[i + gap_int] = temp;
                swapped = 1;
            }
        }
    }
}