int func0(int *arr, int *dep, int n)
{
    int i, j, k, count, max;

    qsort(arr, (size_t)n, sizeof(int), compare);
    qsort(dep, (size_t)n, sizeof(int), compare);

    i = 1;
    j = 0;
    count = 1;
    max = 1;
    while (i < n && j < n) {
        if (arr[i] > dep[j]) {
            count--;
            j++;
        } else {
            count++;
            i++;
            if (count > max)
                max = count;
        }
    }

    return max;
}