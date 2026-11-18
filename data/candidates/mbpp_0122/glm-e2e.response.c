int func0(int n) {
    int arr[3000];
    int result[3000];
    int count = 0;

    memset(arr, 0, sizeof(arr));

    for (int i = 2; i < 3000; i++) {
        if (arr[i] == 0) {
            arr[i] = 1;
            for (int j = 2 * i; j < 3000; j += i) {
                arr[j]--;
                if (arr[j] + 3 == 0) {
                    result[count++] = j;
                }
            }
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }

    return result[n - 1];
}