int func0(int *arrival_times, int *departure_times, int num_events)
{
    // Sort arrival times in ascending order
    qsort(arrival_times, (long)num_events, 4, compare);
    // Sort departure times in ascending order
    qsort(departure_times, (long)num_events, 4, compare);
    
    // Initialize the number of platforms needed to 1 (at least one platform is required)
    int current_platforms = 1;
    // Initialize the maximum number of platforms needed to 1
    int max_platforms = 1;
    // Initialize index for arrival times array
    int arrival_index = 1;
    // Initialize index for departure times array
    int departure_index = 0;
    
    // Iterate through both arrays to calculate the maximum number of platforms needed
    while (arrival_index < num_events && departure_index < num_events) {
        // If the current departure time is less than the current arrival time,
        // a platform becomes free
        if (departure_times[departure_index] < arrival_times[arrival_index]) {
            current_platforms--;
            departure_index++;
        } else {
            // Otherwise, a new platform is needed
            current_platforms++;
            arrival_index++;
            // Update the maximum number of platforms needed if current count exceeds it
            if (max_platforms < current_platforms) {
                max_platforms = current_platforms;
            }
        }
    }
    // Return the maximum number of platforms needed
    return max_platforms;
}