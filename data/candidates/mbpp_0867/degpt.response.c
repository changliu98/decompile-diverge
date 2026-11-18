int func0(int *numbers, int count)
{
    // Initialize counter for odd numbers
    int oddCount = 0;
    // Iterate through the array to count odd numbers
    for (int index = 0; index < count; index++) {
        // Check if the current element is odd
        if (numbers[index] % 2 != 0) {
            oddCount++;
        }
    }
    // Return 2 if the count of odd numbers is even, otherwise return 1
    return (oddCount % 2 == 0) ? 2 : 1;
}