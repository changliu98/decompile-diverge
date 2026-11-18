void minmax(int *arr, int size, int *min, int *max)
{
    if (*arr < *min)
        *min = *arr;
    if (*arr > *max)
        *max = *arr;
}