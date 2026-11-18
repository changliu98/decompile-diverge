void merge_sort(int *array, int length)
{
    if (length < 2)
        return;
    int mid = length / 2;
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((length - mid) * sizeof(int));
    int i;
    for (i = 0; i < mid; i++)
        left[i] = array[i];
    for (i = mid; i < length; i++)
        right[i - mid] = array[i];
    merge_sort(left, mid);
    merge_sort(right, length - mid);
    merge(left, mid, right, length - mid, array);
    free(left);
    free(right);
}