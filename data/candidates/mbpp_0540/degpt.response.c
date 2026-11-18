int func0(int *numbers, int size)
{
    // Sort the array in ascending order to group identical elements together
    sortArray(numbers, size);
    
    // Initialize max_count to 0 (minimum possible consecutive duplicate count)
    int longest_run = 0;
    // Initialize min_count to n (maximum possible consecutive duplicate count)
    int shortest_run = size;
    // Initialize count to 0 to track the number of consecutive duplicates
    int current_run = 0;
    
    // Iterate through the sorted array to find consecutive duplicate elements
    for (int index = 0; index < size - 1; index++) {
        // If current element is equal to the next element, increment the count
        if (numbers[index] == numbers[index + 1]) {
            current_run++;
        } else {
            // When a sequence of duplicates ends, update max_count if current count is greater
            if (current_run > longest_run) longest_run = current_run;
            // Update min_count if current count is smaller
            if (current_run < shortest_run) shortest_run = current_run;
            // Reset count for the next sequence
            current_run = 0;
        }
    }
    
    // Return the difference between the maximum and minimum consecutive duplicate counts
    return longest_run - shortest_run;
}