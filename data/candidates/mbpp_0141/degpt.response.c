void func0(int *arr, int n)
{
    // Iterate through the array, reducing the unsorted portion size by 1 each time
    for (int unsorted_length = n; 1 < unsorted_length; unsorted_length--) {
        // Find the index of the maximum element in the unsorted portion
        int max_index = find_max_index(arr, unsorted_length);
        // If the maximum element is not already at the end of the unsorted portion
        if (max_index != unsorted_length - 1) {
            // Reverse the array from the start to the maximum element's position
            reverse(arr, 0, max_index);
            // Reverse the entire unsorted portion to move the maximum element to the end
            reverse(arr, 0, unsorted_length - 1);
        }
    }
}