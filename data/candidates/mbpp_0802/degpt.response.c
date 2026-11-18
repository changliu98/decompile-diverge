int func0(int *numbers, int size)
{
    int index = 1;
    // Find the first index i where arr[i] < arr[i-1]
    // or i reaches n, indicating the end of a non-decreasing sequence
    while (index < size && numbers[index] >= numbers[index - 1]) {
        index++;
    }
    return index;
}