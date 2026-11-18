int func0(int n) {
    int result = -1;
    
    // Divide out all factors of 2
    while (n % 2 == 0) {
        result = 2;
        n = n / 2;
    }
    
    // Check odd factors from 3 upward
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            result = i;
            n = n / i;
        }
    }
    
    // If remaining n is a prime greater than 2
    if (n > 2) {
        result = n;
    }
    
    return result;
}