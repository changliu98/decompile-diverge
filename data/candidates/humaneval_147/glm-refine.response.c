int __cdecl func0(int n)
{
    int *a = (int *)malloc(sizeof(int) * n);
    int **sum = (int **)malloc(sizeof(int *) * (n + 1));
    int **sum2 = (int **)malloc(sizeof(int *) * (n + 1));

    // Allocate and initialize the 2D arrays
    for (int i = 0; i <= n; ++i)
    {
        sum[i] = (int *)calloc(3, sizeof(int));
        sum2[i] = (int *)calloc(3, sizeof(int));
    }

    // First pass: populate array `a` and build prefix sums of single elements
    for (int i = 1; i <= n; ++i)
    {
        a[i - 1] = (i * i - i + 1) % 3;
        
        for (int j = 0; j < 3; ++j)
            sum[i][j] = sum[i - 1][j];
            
        sum[i][a[i - 1]]++;
    }

    // Second pass: compute combinations of 2 and 3 elements using DP
    for (int times = 1; times < 3; ++times)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < 3; ++j)
                sum2[i][j] = sum2[i - 1][j];

            // The condition `i >= 1` is always true in this loop, so it's omitted
            for (int j = 0; j <= 2; ++j)
            {
                int new_mod = (j + a[i - 1]) % 3;
                sum2[i][new_mod] += sum[i - 1][j];
            }
        }

        // Copy sum2 back to sum, and reset sum2 for the next iteration
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                sum[i][j] = sum2[i][j];
                sum2[i][j] = 0;
            }
        }
    }

    // The result is the number of combinations whose sum modulo 3 is 0
    int result = sum[n][0];

    // Memory cleanup
    for (int i = 0; i <= n; ++i)
    {
        free(sum[i]);
        free(sum2[i]);
    }
    free(sum);
    free(sum2);
    free(a);

    return result;
}