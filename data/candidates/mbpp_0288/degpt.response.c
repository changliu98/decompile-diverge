int func0(int *arr, int N, int P)
{
    int count = 0; // Initialize counter for elements satisfying the condition
    for (int i = 0; i < N; i++) {
        // Check if the square of the current element modulo P equals 1
        if ((arr[i] * arr[i]) % P == 1) {
            count++; // Increment counter if condition is met
        }
    }
    return count; // Return the total count of elements satisfying the condition
}