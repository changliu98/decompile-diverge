int __cdecl func0(int *arr, int n, int k)
{
    int i;
    int max_val = arr[0];
    int total_ops = 0;

    // Phase 1: Find the maximum value in the array
    for (i = 1; i < n; ++i)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    // Phase 2: Calculate operations needed to raise all elements to max_val
    for (i = 0; i < n; ++i)
    {
        int diff = max_val - arr[i];

        // If the difference is not a multiple of k, it's impossible to equalize
        if (diff % k != 0)
        {
            return -1;
        }

        total_ops += diff / k;
    }

    return total_ops;
}