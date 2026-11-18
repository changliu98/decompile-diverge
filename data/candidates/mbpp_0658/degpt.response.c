int func0(int *input_array, int array_size)
{
    // Initialize result with the first element of the list
    int most_frequent_element = *input_array;
    // Initialize max_val to track the highest frequency found so far
    int highest_frequency = 0;
    // Iterate through each element in the list
    for (int current_index = 0; current_index < array_size; current_index++) {
        // Initialize occurrence counter for the current element
        int current_frequency = 0;
        // Count how many times the current element appears in the list
        for (int comparison_index = 0; comparison_index < array_size; comparison_index++) {
            if (input_array[comparison_index] == input_array[current_index]) {
                current_frequency++;
            }
        }
        // Update result and max_val if the current element has a higher frequency
        if (highest_frequency < current_frequency) {
            highest_frequency = current_frequency;
            most_frequent_element = input_array[current_index];
        }
    }
    // Return the element with the highest frequency
    return most_frequent_element;
}