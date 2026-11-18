int *func0(int *numbers, int size, int delimiter, int *out_size) {
    *out_size = size > 0 ? (size * 2) - 1 : 0;
    int *out_numbers = malloc((size_t)(*out_size) * sizeof(int));

    int i = 0;
    int j = 0;
    if (size > 0) {
        out_numbers[0] = numbers[0];
    }
    for (i = 1, j = 1; i < size; i++, j += 2) {
        out_numbers[j] = delimiter;
        out_numbers[j + 1] = numbers[i];
    }

    return out_numbers;
}