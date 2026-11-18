int func0(int *arr, int n)
{
    // Initialize max_so_far to the minimum possible integer value to handle negative numbers correctly
    int max_sum = -0x80000000;
    // max_ending_here stores the maximum sum of the subarray ending at the current position
    int current_sum = 0;
    // start and end will store the starting and ending indices of the maximum sum subarray
    int start_idx = 0;
    int end_idx = 0;
    // s is the temporary start index for the current subarray being considered
    int temp_start = 0;
    // Iterate through each element in the array
    for (int idx = 0; idx < n; idx++) {
        // Add the current element to the running sum of the subarray ending at i
        current_sum += arr[idx];
        // If the current running sum is greater than the maximum sum found so far, update max_so_far and the subarray boundaries
        if (max_sum < current_sum) {
            start_idx = temp_start;
            end_idx = idx;
            max_sum = current_sum;
        }
        // If the running sum becomes negative, reset it to 0 and update the temporary start index to the next element
        if (current_sum < 0) {
            current_sum = 0;
            temp_start = idx + 1;
        }
    }
    // Return the length of the maximum sum subarray
    return end_idx - start_idx + 1;
}