int func0(int *arr, int left, int right)
{
    // Base case: if the left index exceeds the right index, the search range is empty
    if (left <= right) {
        // Calculate the middle index to avoid potential integer overflow
        int middle = left + (right - left) / 2;
        
        // If the element at mid equals its index, search the right half
        if (arr[middle] == middle) {
            return func0(arr, middle + 1, right);
        } 
        // Otherwise, search the left half
        else {
            return func0(arr, left, middle - 1);
        }
    }
    // Return the left index when the search range is exhausted
    return left;
}