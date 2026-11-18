void func0(int *a, int n)
{
    int i, maxim = a[0], exp = 1, index;
    int *sorted, *elem_count;

    for (i = 1; i < n; i++)
    {
        if (a[i] > maxim)
            maxim = a[i];
    }
    sorted = (int *)malloc(n * sizeof(int));
    elem_count = (int *)malloc(10 * sizeof(int));

    while (exp <= maxim)
    {
        for(i=0;i<10;i++)
        {
            elem_count[i]=0;
        }

        for (i = 0; i < n; i++)
        {
            elem_count[(a[i] / exp) % 10]++;
        }

        for (i = 1; i <10; i++)
        {
            elem_count[i] += elem_count[i - 1];
        }

        for (i = n - 1; i >= 0; i--)
        {
            index=(a[i] / exp) % 10;
            sorted[elem_count[index] - 1] = a[i];
            elem_count[index]--;
        }

        for (i = 0; i < n; i++)
        {
            a[i] = sorted[i];
        }

        exp *= 10;
    }
    free(sorted);
    free(elem_count);
}