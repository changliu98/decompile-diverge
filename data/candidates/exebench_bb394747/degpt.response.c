// Finds the smallest power of two greater than or equal to *size
// Updates *size to this power of two
// Returns the bitmask (power of two minus one) for hash table indexing
int get_hashmask(int *target_size)
{
    int power_of_two;
    // Find the smallest power of two that is >= *size
    for (power_of_two = 1; power_of_two < *target_size; power_of_two = power_of_two << 1) {
    }
    // Update the original size to the calculated power of two
    *target_size = power_of_two;
    // Return the bitmask for efficient modulo operations
    return power_of_two - 1;
}