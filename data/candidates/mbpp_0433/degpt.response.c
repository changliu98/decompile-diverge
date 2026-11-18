void func0(int *numbers, int count, int target)
{
    // Sort the array in ascending order using bubble sort
    for (int outer_index = 0; outer_index < count - 1; outer_index++) {
        // Inner loop to compare adjacent elements
        for (int inner_index = 0; inner_index < count - outer_index - 1; inner_index++) {
            // Swap if the current element is greater than the next one
            if (numbers[inner_index + 1] < numbers[inner_index]) {
                int swap_value = numbers[inner_index];
                numbers[inner_index] = numbers[inner_index + 1];
                numbers[inner_index + 1] = swap_value;
            }
        }
    }
    // Compare the last element of the sorted array with the given number
    if (numbers[count - 1] < target) {
        printf("Yes, the entered number is greater than those in the array\n");
    } else {
        printf("No, entered number is less than those in the array\n");
    }
}