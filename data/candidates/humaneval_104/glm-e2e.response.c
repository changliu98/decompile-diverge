void func0(int *arr, int n, int **out_arr, int *out_count) {
    int *res = malloc(n * sizeof(int));
    *out_arr = res;
    *out_count = 0;

    for (int i = 0; i < n; i++) {
        int num = arr[i];
        char is_zero = 0;
        if (num == 0) {
            is_zero = 1;
        }

        char flag = 0;
        while (num > 0) {
            flag = is_zero ^ 0xff;
            if (num % 2 == 0) {
                is_zero = 1;
            }
            num /= 10;
        }

        if (!is_zero) {
            res[*out_count] = arr[i];
            (*out_count)++;
        }
    }

    for (int i = 0; i < *out_count - 1; i++) {
        for (int j = 0; j < *out_count - i - 1; j++) {
            if (res[j] > res[j + 1]) {
                int temp = res[j];
                res[j] = res[j + 1];
                res[j + 1] = temp;
            }
        }
    }
}