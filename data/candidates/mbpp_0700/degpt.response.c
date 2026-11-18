// Function to count elements within a specified range [min, max]
int func0(int *numbers, int count, int lower_bound, int upper_bound)
{
    int valid_count = 0; // Counter for elements within the range
    for (int index = 0; index < count; index++) {
        // Check if current element is within the range [min, max]
        if (numbers[index] >= lower_bound && numbers[index] <= upper_bound) {
            valid_count++; // Increment counter if element is within range
        }
    }
    return valid_count; // Return the count of elements within the range
}