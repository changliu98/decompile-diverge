int func0(int *jumps, int size)
{
    // If array is empty or first element is zero, return max integer (unreachable)
    if (size == 0 || *jumps == 0) {
        return 0x7fffffff;
    }

    // dp[i] stores the minimum number of jumps to reach index i
    int min_jumps[size];
    min_jumps[0] = 0;
    for (int current_index = 1; current_index < size; current_index++) {
        // Initialize dp[i] to max integer (unreachable)
        min_jumps[current_index] = 0x7fffffff;
        for (int previous_index = 0; previous_index < current_index; previous_index++) {
            // Check if index j can reach index i
            if (current_index <= previous_index + jumps[previous_index] && min_jumps[previous_index] != 0x7fffffff) {
                int candidate_jumps = min_jumps[previous_index] + 1;
                // Update dp[i] with the minimum jumps
                if (candidate_jumps < min_jumps[current_index]) {
                    min_jumps[current_index] = candidate_jumps;
                }
                // Break early since we found a valid path to i
                break;
            }
        }
    }
    // Return the minimum jumps to reach the last index
    return min_jumps[size - 1];
}