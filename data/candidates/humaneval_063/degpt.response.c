int func0(int n)
{
    int fibonacci_values[100]; // Array to store computed values
    memset(fibonacci_values, 0, 400); // Initialize array with zeros
    fibonacci_values[1] = 0; // Base case: first element
    fibonacci_values[2] = 1; // Base case: second element
    for (int i = 3; i <= n; i++) {
        fibonacci_values[i] = fibonacci_values[i - 1] + fibonacci_values[i - 2] + fibonacci_values[i - 3]; // Compute current value as sum of previous three values
    }
    return fibonacci_values[n]; // Return the nth value
}