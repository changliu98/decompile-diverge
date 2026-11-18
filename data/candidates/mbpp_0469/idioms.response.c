int func0(int *price, int n, int k)
{
    int i; int j; int l;
    int *max_so_far = (int *)((char *)price + (sizeof(int)*(n)));
    int *max_ending_here = (int *)((char *)max_so_far + (sizeof(int)*((k+1)*n)));
    for (i = 0; i <= k; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == 0 || j == 0)
            {
                max_ending_here[i*n + j] = 0;
            }
            else
            {
                int max = 0;
                for (l = 0; l < j; l++)
                {
                    int curr_price = max_ending_here[(i - 1)*n + l] +
                                      price[j] - price[l];
                    if (max < curr_price)
                        max = curr_price;
                }
                if (max > max_ending_here[i*n + j - 1])
                    max_ending_here[i*n + j] = max;
                else
                    max_ending_here[i*n + j] = max_ending_here[i*n + j - 1];
            }
        }
    }
    return max_ending_here[k*n + n - 1];
}