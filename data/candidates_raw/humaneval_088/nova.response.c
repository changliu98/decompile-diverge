void func0(int *arr, int n, int **p, int *q) {
    int i, j, temp, flag;
    *q = n;
    if (n == 0)
        *p = NULL;
    else
        *p = (int *)malloc(n * sizeof(int));
    if (*p == NULL)
        exit(1);
    for (i = 0; i < n; i++)
        (*p)[i] = arr[i];
    for (i = 0; i < n - 1; i++) {
        flag = 0;
        for (j = i + 1; j < n; j++) {
            if ((*p)[i] > (*p)[j]) {
                temp = (*p)[i];
                (*p)[i] = (*p)[j];
                (*p)[j] = temp;
                flag = 1;
            }
            if (flag)
                break;
        }
    }
}