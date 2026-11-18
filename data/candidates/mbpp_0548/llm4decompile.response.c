int func0(int arr[], int n)
{
    int longest_increasing_subsequence[n];
    int i, j, maximum;

    for (i = 0; i < n; i++)
        longest_increasing_subsequence[i] = 1;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[j] < arr[i] && longest_increasing_subsequence[i] < longest_increasing_subsequence[j] + 1)
                longest_increasing_subsequence[i] = longest_increasing_subsequence[j] + 1;

    maximum = 0;
    for (i = 0; i < n; i++)
        if (maximum < longest_increasing_subsequence[i])
            maximum = longest_increasing_subsequence[i];

    return maximum;
}