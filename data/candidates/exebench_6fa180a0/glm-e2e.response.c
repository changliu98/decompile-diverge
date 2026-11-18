void sortVrtx(int *arr) {
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = 1; i < 3; i++) {
            if (arr[i - 1] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
    }
}