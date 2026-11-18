int func0(int n)
{
    // Initialize cnt with the count of odd numbers in the range [1, n]
    int count = (n + 1) / 2;
    // Set iVar1 to n + 1 for boundary calculations
    int upperBound = n + 1;
    // Iterate through powers of 2 up to iVar1
    for (int currentPowerOfTwo = 2; currentPowerOfTwo <= upperBound; currentPowerOfTwo = currentPowerOfTwo << 1) {
        // Add the contribution of even numbers divisible by the current power of 2
        count = ((upperBound / currentPowerOfTwo) / 2) * currentPowerOfTwo + count;
        // If the current power of 2 divides into iVar1 with an odd quotient,
        // add the remaining elements that are multiples of the current power of 2
        if ((upperBound / currentPowerOfTwo & 1U) != 0) {
            count = upperBound % currentPowerOfTwo + count;
        }
    }
    // Return the total count of numbers divisible by at least one power of 2 in the range [1, n]
    return count;
}