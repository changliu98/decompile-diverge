int func0(int n)
{
    int fibonacci_sequence[1000]; // Array to store Fibonacci numbers, max index 999
    memset(fibonacci_sequence, 0, 4000); // Initialize array with zeros (1000 * 4 bytes)
    fibonacci_sequence[0] = 0; // Base case: F(0) = 0
    fibonacci_sequence[1] = 1; // Base case: F(1) = 1
    for (int i = 2; i <= n; i++) {
        fibonacci_sequence[i] = fibonacci_sequence[i - 1] + fibonacci_sequence[i - 2]; // Compute F(i) = F(i-1) + F(i-2)
    }
    return fibonacci_sequence[n]; // Return the nth Fibonacci number
}