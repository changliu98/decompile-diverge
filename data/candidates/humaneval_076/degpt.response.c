int func0(int value, int base)
{
    // Return 0 if either x or n is non-positive, as they are invalid inputs
    if (value <= 0 || base <= 0) return 0;
    
    // Initialize p to 1 (n^0) and count to 0 (exponent)
    int power = 1;
    int exponent = 0;
    
    // Loop up to 99 times to check if x is a power of n
    while (exponent < 99) {
        // If p equals x, then x is a power of n
        if (power == value) return 1;
        
        // Multiply p by n to get the next power of n
        power = power * base;
        
        // Increment the exponent count
        exponent = exponent + 1;
    }
    
    // If x is not found as a power of n within 99 iterations, return 0
    return 0;
}