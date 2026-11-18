int largest_prime_factor(int n)
{
    int i, maxPrime = -1;
    while (n % 2 == 0){
        maxPrime = 2;
        n = n>>1;
    }
    for (i = 3; i <= sqrt((double)n); i += 2){
        while (n % i == 0){
            maxPrime = i;
            n = n/i;
        }
    }
    if (n > 2)
        maxPrime = n;
    return maxPrime;
}