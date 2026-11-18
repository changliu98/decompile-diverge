void func0(int *numbers, int size)
{
    // Initialize out_of_place to -1, indicating no out-of-place element found yet
    int misplaced_index = -1;
    // Iterate through each element in the array
    for (int current_index = 0; current_index < size; current_index++) {
        // If an out-of-place element was previously identified
        if (misplaced_index != -1 &&
            // Check if current element has opposite sign to the out-of-place element
            ((numbers[current_index] > 0 && numbers[misplaced_index] < 0) ||
             (numbers[current_index] < 0 && numbers[misplaced_index] > 0))) {
            // Right-rotate the subarray from out_of_place to index
            right_rotate(numbers, size, misplaced_index, current_index);
            // If the distance between current and out-of-place index is less than 3,
            // reset out_of_place to -1 (no more out-of-place element)
            if (current_index - misplaced_index < 3) {
                misplaced_index = -1;
            } else {
                // Otherwise, update out_of_place by adding 2 to skip over the rotated elements
                misplaced_index += 2;
            }
        }
        // If no out-of-place element is currently tracked
        if (misplaced_index == -1 &&
            // Check if current element is in the wrong position based on sign and index parity:
            // Positive numbers should be at even indices, negative at odd indices
            ((numbers[current_index] > 0 && current_index % 2 == 0) ||
             (numbers[current_index] < 0 && current_index % 2 == 1))) {
            // Mark current index as the out-of-place element
            misplaced_index = current_index;
        }
    }
}