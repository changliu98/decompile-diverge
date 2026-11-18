int* func0(int* arr, int n) {
    int* out = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        char str[32];
        sprintf(str, "%d", abs(arr[i]));
        int len = strlen(str);
        int sum = 0;
        for (int j = 1; j < len; j++) {
            sum += str[j] - '0';
        }
        if (arr[i] > 0) {
            sum += str[0] - '0';
        } else {
            sum -= str[0] - '0';
        }
        out[i] = sum;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (out[j - 1] > out[j]) {
                int temp = out[j];
                out[j] = out[j - 1];
                out[j - 1] = temp;

                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }

    free(out);
    return arr;
}