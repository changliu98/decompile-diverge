double func0(int *array, int length)
{
    int sum = 0; // Initialize total sum to zero
    for (int index = 0; index < length; index++) {
        sum += array[index]; // Accumulate the sum of array elements
    }
    return (double)sum / length; // Return the average as a double
}