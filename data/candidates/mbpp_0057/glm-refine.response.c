int __cdecl func0(int *arr, int n)
{
    int i, j, temp;

    // Sort the array in descending order using an exchange sort
    for (i = 0; i < n - 1; ++i)
    {
        for (j = i + 1; j < n; ++j)
        {
            if (arr[i] < arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Evaluate the polynomial: arr[0]*10^(n-1) + arr[1]*10^(n-2) + ... + arr[n-1]
    int result = arr[0];
    for (i = 1; i < n; ++i)
    {
        result = arr[i] + 10 * result;
    }

    return result;
}