int __cdecl factors(int M, int *arr)
{
    int i = 0;
    
    // Initial trial divisions by specific primes and composites.
    // The order and values are preserved exactly as in the original.
    int initial_divisors[] = {53, 47, 43, 41, 37, 31, 29, 23, 19, 17, 13, 11, 8, 7, 5, 4, 3, 2};
    for (size_t j = 0; j < sizeof(initial_divisors) / sizeof(initial_divisors[0]); ++j)
    {
        int d = initial_divisors[j];
        while (M % d == 0)
        {
            arr[i++] = d;
            M /= d;
        }
    }
    
    // If M > 31, proceed with the 6k ± 1 optimization for larger prime factors.
    if (M > 31)
    {
        int num = 2;
        while (M > 1)
        {
            int m1 = 6 * num - 1;
            int m2 = 6 * num + 1;
            
            while (M % m1 == 0)
            {
                arr[i++] = m1;
                M /= m1;
            }
            while (M % m2 == 0)
            {
                arr[i++] = m2;
                M /= m2;
            }
            ++num;
        }
    }
    
    return i;
}