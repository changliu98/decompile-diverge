void sort(int *arr, int n, int **sorted, int *m) {
    *m = n;
    if (n == 0) {
        *sorted = NULL;
        return;
    }

    *sorted = (int *) malloc(n * sizeof(int));
    if (*sorted == NULL) exit(1);

    for (int i = 0; i < n; i++) {
        (*sorted)[i] = arr[i];
    }

    bool shouldSortAscending = ((arr[0] + arr[n - 1]) % 2 == 1) ? true : false;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (shouldSortAscending) {
                if ((*sorted)[i] > (*sorted)[j]) {
                    int temp = (*sorted)[i];
                    (*sorted)[i] = (*sorted)[j];
                    (*sorted)[j] = temp;
                }
            } else {
                if ((*sorted)[i] < (*sorted)[j]) {
                    int temp = (*sorted)[i];
                    (*sorted)[i] = (*sorted)[j];
                    (*sorted)[j] = temp;
                }
            }
        }
    }
}