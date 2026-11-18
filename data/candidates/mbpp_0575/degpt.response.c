int func0(int divisor, int target_count, int range_start, int range_end) {
    int non_multiple_count = 0; // Initialize counter for non-multiples of A
    int current_number = range_start;     // Start checking from lower bound L
    while (current_number <= range_end) { // Iterate through the range [L, R]
        if (current_number % divisor != 0) { // Check if current number is not a multiple of A
            non_multiple_count++;       // Increment counter for non-multiples
        }
        if (non_multiple_count == target_count) { // If we have found the N-th non-multiple
            return current_number;      // Return the current number
        }
        current_number++;             // Move to the next number
    }
    return current_number;            // Return i if N non-multiples are not found within the range
}