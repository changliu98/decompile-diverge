// Recursive function to calculate the sum of integers from 1 to *n
// Parameters:
//   n: pointer to the current integer value (decremented in each recursive call)
//   s: pointer to the accumulator for the sum
// Returns: 1 when *n reaches 0 (base case)
int summe(int *current_value, int *accumulator) {
    // Base case: if *n is not zero, continue recursion
    if (*current_value != 0) {
        // Add the current value of *n to the accumulator *s
        *accumulator = *current_value + *accumulator;
        // Decrement *n by 1
        *current_value = *current_value - 1;
        // Recursive call with updated values
        return summe(current_value, accumulator);
    }
    // Base case: when *n is 0, return 1
    return 1;
}