int __cdecl func0(int n)
{
    int prime_count = 0;

    for (int num = 0; num < n; ++num)
    {
        if (num > 1)
        {
            int is_prime = 1;
            for (int i = 2; i < num; ++i)
            {
                if (num % i == 0)
                {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime)
            {
                ++prime_count;
            }
        }
    }
    
    return prime_count;
}