// Function to count the number of inversions in an array
// An inversion is a pair of indices (i, j) such that i < j and arr[i] > arr[j]
int func0(int *array, int size)
{
    int inversion_count = 0; // Initialize inversion count to zero
    for (int index_i = 0; index_i < size; index_i++) { // Iterate through each element of the array
        for (int index_j = index_i + 1; index_j < size; index_j++) { // Compare with all subsequent elements
            if (array[index_j] < array[index_i]) { // Check if an inversion is found
                inversion_count++; // Increment the inversion count
            }
        }
    }
    return inversion_count; // Return the total number of inversions
}