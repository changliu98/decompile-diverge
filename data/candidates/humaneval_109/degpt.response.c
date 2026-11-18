// Function to check if the array is sorted (non-decreasing) or can be made sorted by rotating it.
// Returns true if the array is sorted or can be sorted by rotation, false otherwise.
_Bool func0(int *arr, int size)
{
    // An empty array is considered sorted.
    if (size == 0) {
        return true;
    }
    int rotation_count = 0;
    // Count the number of times an element is less than its previous element.
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            rotation_count++;
        }
    }
    // Check if the last element is less than the first element.
    // This indicates a potential rotation point.
    if (arr[0] < arr[size - 1]) {
        rotation_count++;
    }
    // If there are fewer than 2 such occurrences, the array is sorted or can be sorted by rotation.
    return rotation_count < 2;
}