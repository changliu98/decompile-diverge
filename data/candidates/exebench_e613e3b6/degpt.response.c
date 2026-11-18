// Function to calculate intervals of consecutive zeros in the stalls array
// Parameters:
//   stalls: array representing stall states (0 for empty, non-zero for occupied)
//   intervals: output array to store the lengths of consecutive zero intervals
//   num: total number of elements in the stalls array
// Returns: the total number of intervals found (including the final partial interval if any)
int cal_intervals(int *stall_states, int *interval_lengths, int array_size)
{
    int interval_count = 0;  // Counter for the number of complete intervals found
    int index = 0;     // Index variable for traversing the stalls array

    // Skip leading zeros (empty stalls at the beginning)
    while (index < array_size && stall_states[index] == 0) {
        index++;
    }

    // Process the rest of the stalls array
    while (index < array_size) {
        // Skip over occupied stalls (non-zero values)
        while (index < array_size && stall_states[index] != 0) {
            index++;
        }
        int current_interval_length = 0;  // Counter for the current interval of consecutive zeros
        // Count consecutive zeros (empty stalls)
        while (index < array_size && stall_states[index] == 0) {
            index++;
            current_interval_length++;
        }
        // If there are more elements after the current interval, store the interval length
        if (index < array_size) {
            interval_lengths[interval_count] = current_interval_length;
            interval_count++;
        }
    }
    // Return the total number of intervals (segs complete intervals plus one more if the array ended with zeros)
    return interval_count + 1;
}