void func0(int *a, int n, int **b, int *k) {
    int i, j, t;
    *b = (int *)malloc(n * sizeof(int));
    *k = 0;
    for (i = 0; i < n;) {
        t = a[i];
        bool flag = false;
        if (t == 0)
            flag = true;
        while (t > 0) {
            if (t % 2 == 0)
                t /= 2;
            else {
                if (flag)
                    flag = false;
                t /= 10;
            }
        }
        if (!flag) {
            (*b)[*k] = a[i];
            (*k)++;
        } else {
            for (j = 0; j < *k - 1; j++) {
                if ((*b)[j] > (*b)[j + 1]) {
                    t = (*b)[j];
                    (*b)[j] = (*b)[j + 1];
                    (*b)[j + 1] = t;
                }
            }
        }
        i++;
    }
}