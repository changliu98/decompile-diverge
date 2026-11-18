#include <math.h>

// Finds the largest prime factor of a given integer n using trial division.
int __cdecl largest_prime_factor(int n)
{
    int factor;
    int max_prime = -1;

    // Divide out all factors of 2
    while (n % 2 == 0)
    {
        max_prime = 2;
        n /= 2;
    }

    // Check for odd factors from 3 up to sqrt(n)
    // Note: sqrt is kept to prevent integer overflow that would occur with factor * factor <= n
    for (factor = 3; (double)factor <= sqrt((double)n); factor += 2)
    {
        // While factor divides n, divide n by factor and update max_prime
        while (n % factor == 0)
        {
            max_prime = factor;
            n /= factor;
        }
    }

    // If n is still greater than 2, then it is a prime number
    // and is the largest prime factor.
    if (n > 2)
    {
        return n;
    }

    return max_prime;
}