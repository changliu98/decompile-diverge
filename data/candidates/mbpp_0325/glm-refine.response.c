int __cdecl func0(int n)
{
    // Base case: if n is 0, 1, 2, or 3, the minimum number of perfect squares is n itself.
    if (n <= 3)
        return n;

    int res = n;

    // Iterate through all possible perfect squares (x * x) up to n
    for (int x = 1; x * x <= n; ++x)
    {
        int temp = x * x;
        
        // Recursively find the minimum perfect squares for the remainder
        int current = func0(n - temp) + 1;
        
        // Keep track of the minimum result found
        if (current < res)
            res = current;
    }

    return res;
}