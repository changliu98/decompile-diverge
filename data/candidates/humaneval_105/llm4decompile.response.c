void func0(int *arr, int size, char ***out, int *out_size)
{
    int i, j;
    char *names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    *out_size = 0;
    for (i = size - 1; i >= 0; i--) {
        if (arr[i] > 0 && arr[i] < 10) {
            *out_size += 1;
        }
    }

    *out = (char **)malloc((size_t)(*out_size) * sizeof(char *));
    for (i = size - 1, j = 0; i >= 0 && j < *out_size; i--) {
        if (arr[i] > 0 && arr[i] < 10) {
            (*out)[j++] = names[arr[i]];
        }
    }
}