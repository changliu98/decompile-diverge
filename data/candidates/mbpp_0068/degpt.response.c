// Function to check if an array is sorted in either non-decreasing or non-increasing order
_Bool func0(int *arr, int size) {
    // Base case: arrays with 0 or 1 element are always sorted
    if (size <= 1) return true;
    
    // Initialize flags to track if the array is non-decreasing or non-increasing
    bool is_non_decreasing = true;
    bool is_non_increasing = true;
    
    // Iterate through the array to check the order of adjacent elements
    for (int index = 0; index < size - 1; index++) {
        // If current element is less than the next, it's not non-increasing
        if (arr[index] < arr[index + 1]) is_non_increasing = false;
        // If current element is greater than the next, it's not non-decreasing
        if (arr[index] > arr[index + 1]) is_non_decreasing = false;
    }
    
    // Return true if the array is either non-decreasing or non-increasing
    return is_non_decreasing || is_non_increasing;
}