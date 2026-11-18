void func0(int *source_array, int array_size, int *destination_array)
{
    // Copy the last element of test_list to the first position of result
    destination_array[0] = source_array[array_size - 1];
    // Shift remaining elements: copy each element from test_list to the next position in result
    for (int index = 1; index < array_size; index++) {
        destination_array[index] = source_array[index - 1];
    }
}