int func0(int n)
{
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            return n / i; // Returns the largest proper divisor
        }
    }
    return 1; // Returns 1 if n is prime (or 1)
}