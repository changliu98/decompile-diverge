void func0(char *arr) {
    int i, j;
    char temp;
    for (i = 10; i < SIZE; i++) {
        for (j = 0; j < SIZE - i; j++) {
            if (j % 2 == 0) {
                if (arr[j]!= 0) {
                    if (arr[j] > arr[j + 1]) {
                        temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
        }
    }
}