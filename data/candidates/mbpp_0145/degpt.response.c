// Function to calculate the difference between the maximum and minimum elements in an array
int func0(int *arr, int n)
{
    int index;          // Loop counter
    int maxValue;     // Variable to store the maximum element
    int minValue;     // Variable to store the minimum element
    
    // Initialize min and max with the first element of the array
    minValue = *arr;
    maxValue = *arr;
    
    // Iterate through the array starting from the second element
    for (index = 1; index < n; index = index + 1) {
        // Update minimum element if current element is smaller
        if (arr[index] < minValue) {
            minValue = arr[index];
        }
        // Update maximum element if current element is larger
        if (maxValue < arr[index]) {
            maxValue = arr[index];
        }
    }
    // Return the difference between the maximum and minimum elements
    return maxValue - minValue;
}