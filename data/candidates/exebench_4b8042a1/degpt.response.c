int next_arr_seq(int *sequence, int sequence_length, int max_value)
{
    int index = 0;
    while (1) {
        // If we've exceeded the array length, no more sequences exist
        if (sequence_length <= index) {
            return 0;
        }
        // Increment the current element
        sequence[index] = sequence[index] + 1;
        // If the current element is within the valid range, we're done
        if (sequence[index] <= max_value) break;
        // Reset the current element to 0 and carry over to the next position
        sequence[index] = 0;
        index = index + 1;
    }
    // Successfully generated the next sequence
    return 1;
}