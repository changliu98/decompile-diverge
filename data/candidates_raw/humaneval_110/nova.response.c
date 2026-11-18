char *func0(int *a, int n, int *b, int m) {
    int i, j;
    int count1 = 0, count2 = 0;
    char *res;

    for (i = 0; i < n; i++) {
        if (a[i] % 2 == 0)
            count1++;
        else
            i++;
    }

    for (j = 0; j < m; j++) {
        if (b[j] % 2 == 0)
            count2++;
        else
            j++;
    }

    if (count1 >= n)
        res = "Yes";
    else
        res = "No";

    return res;
}