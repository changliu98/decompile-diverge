int func0(int *numbers, int size)
{
    int distinct_pair_count = 0; // Initialize counter to zero
    for (int first_index = 0; first_index < size; first_index++) { // Iterate through each element
        for (int second_index = first_index + 1; second_index < size; second_index++) { // Compare with subsequent elements
            if (numbers[first_index] != numbers[second_index]) { // Check if elements are different
                distinct_pair_count++; // Increment counter for each pair of different elements
            }
        }
    }
    return distinct_pair_count; // Return the total count of different pairs
}