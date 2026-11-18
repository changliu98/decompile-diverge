int func0(int *arr, int n) {
    int *mls = malloc((size_t)n * sizeof(int));
    int i, j, max = 0;

    for (i = 0; i < n; i++)
        mls[i] = 1;

    for (i = 0; i < n; i++)
        for (j = 0; j < i; j++)
            if (abs(arr[i] - arr[j]) <= 1 && mls[j] + 1 > mls[i])
                mls[i] = mls[j] + 1;

    for (i = 0; i < n; i++)
        if (mls[i] > max)
            max = mls[i];

    free(mls);

    return max;
}