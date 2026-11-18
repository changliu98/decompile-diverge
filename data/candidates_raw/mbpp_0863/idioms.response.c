int longest_increasing_subarray(int *array, int n)
{
    int i; int j; int temp;
    int max = 0; int count = 0;
    int *subarray;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    subarray = (int *)malloc(n * sizeof(int));
    i = 0;
    subarray[i] = array[0];
    i++;
    for (j = 1; j < n; j++)
    {
        if (array[j] != array[j - 1])
        {
            subarray[i] = array[j];
            i++;
        }
    }
    for (i = 0; i < i; i++)
    {
        if (i > 0 && subarray[i] == subarray[i - 1] + 1)
        {
            count++;
        }
        else
        {
            count = 1;
        }
        if (count > max)
        {
            max = count;
        }
    }
    free(subarray);
    return max;
}