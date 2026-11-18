int func0(int N)
{
    // Allocate memory for an array of size N+1 to store sum of divisors
    int *divisor_sums = (int *)malloc((N + 1) * sizeof(int));
    int multiple;
    int current_number;
    int i;

    // Check if memory allocation was successful
    if (divisor_sums == NULL) {
        return 0;
    }

    // Initialize all elements of the array to 0
    for (i = 0; i <= N; i++) {
        divisor_sums[i] = 0;
    }

    // Iterate from 2 to N to compute sum of proper divisors for each number
    for (current_number = 2; current_number <= N; current_number++) {
        // If local_38[i_1] is 0, it means i_1 is prime (not yet processed)
        if (divisor_sums[current_number] == 0) {
            // For each multiple of i_1, add i_1 to its divisor sum
            for (multiple = current_number; multiple <= N; multiple += current_number) {
                divisor_sums[multiple] += current_number;
            }
        }
    }

    // Retrieve the sum of divisors for N
    int result = divisor_sums[N];
    // Free the allocated memory
    free(divisor_sums);
    return result;
}