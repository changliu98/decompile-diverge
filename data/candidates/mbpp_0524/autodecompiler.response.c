int func0(int p[], int n)
{
    int i, j;
    int q = 0;
    int r;
    int r_max = 0;
    int r_array[n];

    for (i = 0; i < n; i++)
        r_array[i] = p[i];

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (p[i] > p[j] && r_array[i] < (r_array[j] + p[i])) {
                r_array[i] = r_array[j] + p[i];
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (r_max < r_array[i])
            r_max = r_array[i];
    }

    return r_max;
}