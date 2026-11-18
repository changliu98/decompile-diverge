int func0(int n) {
    int result = 1;
    
    // Divide n by 2 as long as it is even
    while (n % 2 == 0) {
        n /= 2;
    }
    
    // Check odd numbers up to sqrt(n)
    for (int i = 3; i <= sqrt(n) + 1; i += 2) {
        int count = 0;
        int sum = 1;
        int term = 1;
        
        while (n % i == 0) {
            count++;
            n /= i;
            term *= i;
            sum += term;
        }
        
        result *= sum;
    }
    
    // If n is still greater than or equal to 2, it's a prime factor
    if (n >= 2) {
        result *= (n + 1);
    }
    
    return result;
}