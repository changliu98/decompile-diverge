void sort(int *list, int size, char ***result, int *count) {
    char *name[] = {"", "trel", "hel", "mer", "huh", "merk", "jou", "helmi", "maa", "helmi", "merk", "jou", "helmi"};
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    *count = 0;
    for (i = size - 1; i >= 0; i--) {
        if (list[i] >= 1 && list[i] <= 9) {
            (*count)++;
        }
    }
    *result = (char **)malloc((*count) * sizeof(char *));
    for (i = size - 1, j = 0; i >= 0 && j < *count; i--) {
        if (list[i] >= 1 && list[i] <= 9) {
            (*result)[j++] = name[list[i]];
        }
    }
}