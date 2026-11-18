int largest_prime_factor(int n)
{
    int f;
    if (n % 2 == 0) {
        f = 2;
    } else {
        int i = 3;
        while (1) {
            if (i * i > n) {
                f = n;
                break;
            }
            if (n % i == 0) {
                f = i;
                break;
            }
            i += 2;
        }
    }
    return f;
}