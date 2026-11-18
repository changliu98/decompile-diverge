int func0(int number)
{
    int divisor = 2;
    // Find the smallest divisor of n starting from 2
    while (number >= divisor * divisor) {
        // If i divides n, then i is the smallest divisor
        if (number % divisor == 0) break;
        divisor++;
    }
    // Return the largest divisor of n (which is n divided by its smallest divisor)
    return number / divisor;
}