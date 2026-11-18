void func0(int *x, int size, int **out, int *out_size)
{
    *out = malloc((long)size * sizeof(int));
    *out_size = 0;
    for (int i = 0; i < size; i++) {
        int num = x[i];
        int has_even_digit = 0;
        while (num > 0) {
            if (num % 2 == 0) {
                has_even_digit = 1;
            }
            num /= 10;
        }
        if (!has_even_digit) {
            (*out)[*out_size] = x[i];
            *out_size += 1;
        }
    }

    for (int i = 0; i < *out_size - 1; i++) {
        for (int j = 0; j < *out_size - i - 1; j++) {
            if ((*out)[j] > (*out)[j + 1]) {
                int tmp = (*out)[j];
                (*out)[j] = (*out)[j + 1];
                (*out)[j + 1] = tmp;
            }
        }
    }
}