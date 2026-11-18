void func0(int n, int **arr, int *count) {
    int capacity = 10;
    *count = 1;
    *arr = (int *)realloc(*arr, 1 * sizeof(int));
    (*arr)[0] = 1;

    while (n != 1) {
        if (n % 2 == 1) {
            if (*count >= capacity) {
                capacity *= 2;
                *arr = (int *)realloc(*arr, capacity * sizeof(int));
            }
            int idx = *count;
            (*arr)[idx] = n;
            (*count)++;
            n = n * 3 + 1;
        } else {
            n = n / 2;
        }
    }

    for (int i = 1; i < *count; i++) {
        int temp = (*arr)[i];
        int j = i - 1;
        while (j >= 0 && (*arr)[j] > temp) {
            (*arr)[j + 1] = (*arr)[j];
            j--;
        }
        (*arr)[j + 1] = temp;
    }
}