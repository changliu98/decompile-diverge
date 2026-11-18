void sort(char *arr) {
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < 10 - i && arr[j] != 0; j++) {
            if (arr[j] > arr[j + 1]) {
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}