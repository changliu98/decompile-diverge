int func0(int limit, int modulus, int remainder)
{
    // Initialize ans to the minimum possible integer value
    int result = -0x80000000;
    // Iterate from 0 to n inclusive
    for (int candidate = 0; candidate <= limit; candidate++) {
        // Check if k satisfies the condition: k modulo x equals y
        // and ans is less than k
        if ((candidate % modulus == remainder) && (result < candidate)) {
            // Update ans to the current k if conditions are met
            result = candidate;
        }
    }
    // If ans is negative or greater than n, return -1 indicating no valid value found
    if (result < 0 || limit < result) {
        return -1;
    }
    // Return the largest valid k that satisfies the condition
    return result;
}