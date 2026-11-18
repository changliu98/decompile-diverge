// Function to count the number of negative integers in a given list
int func0(int *numbers, int count)
{
    int negative_count = 0; // Initialize counter for negative numbers
    for (int index = 0; index < count; index++) { // Iterate through each element in the list
        if (numbers[index] < 1) { // Check if the current element is negative
            negative_count++; // Increment the counter for negative numbers
        }
    }
    return negative_count; // Return the total count of negative numbers
}