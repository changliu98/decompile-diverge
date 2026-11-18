int func0(int limit)
{
    int sequence[100]; // Array to store computed values
    sequence[0] = 0; // Base case: f(0) = 0
    sequence[1] = 0; // Base case: f(1) = 0
    sequence[2] = 2; // Base case: f(2) = 2
    sequence[3] = 0; // Base case: f(3) = 0
    for (int i = 4; i <= limit; i++) {
        sequence[i] = sequence[i - 1] + sequence[i - 2] + sequence[i - 3] + sequence[i - 4]; // Compute f(i) as sum of previous four values
    }
    return sequence[limit]; // Return the nth value
}