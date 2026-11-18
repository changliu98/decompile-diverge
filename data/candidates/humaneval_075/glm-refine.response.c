#include <stdbool.h>

// Returns true if 'n' has exactly 3 prime factors (counting multiplicities)
bool has_exactly_three_prime_factors(int n)
{
    int factor_count = 0;

    if (n < 2)
        return false;

    // Check for prime factors up to the square root of n
    for (int i = 2; i * i <= n; ++i)
    {
        // While 'i' divides 'n', it is a prime factor
        while (n % i == 0)
        {
            n /= i;
            factor_count++;
        }
    }

    // If n is still greater than 1, then the remaining n is a prime factor
    if (n > 1)
        factor_count++;

    return factor_count == 3;
}