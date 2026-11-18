int func0(int n) {
    // Initialize factorial result to 1
    int factorialResult = 1;
    // Calculate factorial of n iteratively
    for (int counter = 2; counter <= n; counter++) {
        // Multiply current number to factorial
        factorialResult *= counter;
        // Remove trailing zeros from factorial
        while (factorialResult % 10 == 0) {
            factorialResult /= 10;
        }
    }
    // Extract the last non-zero digit by removing all digits except the last one
    while (factorialResult > 9) {
        factorialResult /= 10;
    }
    // Return the last non-zero digit of n!
    return factorialResult;
}