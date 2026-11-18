int func0(int *numbers, int size)
{
    int total = 0;
    // Iterate through each element in the array
    for (int index = 0; index < size; index++) {
        int occurrences = 1;
        // Count occurrences of arr[i] in the entire array
        for (int compare_index = 0; compare_index < size; compare_index++) {
            // If element at index j matches element at index i and they are not the same instance
            if (numbers[compare_index] == numbers[index] && compare_index != index) {
                occurrences++;
            }
        }
        // If the element appears more than once, add it to the sum
        if (occurrences > 1) {
            total += numbers[index];
        }
    }
    return total;
}