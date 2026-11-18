char * func0(int n)
{
    int divisorCount = 0; // Initialize divisor count to zero
    // Iterate from 1 up to sqrt(n) + 1 to find all divisors
    for (int divisor = 1; divisor < (int)sqrt((double)n) + 2; divisor = divisor + 1) {
        if (n % divisor == 0) { // Check if i is a divisor of n
            if (n / divisor == divisor) {
                // If i is the square root of n, count it once
                divisorCount = divisorCount + 1;
            }
            else {
                // Otherwise, count both i and n/i as divisors
                divisorCount = divisorCount + 2;
            }
        }
    }
    // Return "Even" if the total number of divisors is even, otherwise "Odd"
    if (divisorCount % 2 == 0) {
        return "Even";
    }
    else {
        return "Odd";
    }
}