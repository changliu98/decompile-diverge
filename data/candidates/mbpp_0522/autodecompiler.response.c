int func0(int array[], int size) {
    int inc[size + 1];
    int dec[size + 1];
    int i, j;
    int maximum;

    for (i = 0; i <= size; ++i)
        inc[i] = 1;
    for (i = 1; i < size; ++i)
        for (j = 0; j < i; ++j)
            if (array[i] > array[j] && inc[i] < inc[j] + 1)
                inc[i] = inc[j] + 1;

    for (i = 0; i <= size; ++i)
        dec[i] = 1;
    for (i = size - 2; i >= 0; --i)
        for (j = size - 1; j > i; --j)
            if (array[i] > array[j] && dec[i] < dec[j] + 1)
                dec[i] = dec[j] + 1;

    maximum = inc[0] + dec[0] - 1;
    for (i = 1; i < size; ++i)
        if (inc[i] + dec[i] - 1 > maximum)
            maximum = inc[i] + dec[i] - 1;

    return maximum;
}