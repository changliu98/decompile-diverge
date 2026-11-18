void func0(int *first_array, int first_array_size, int *second_array, int second_array_size, int *combined_array)
{
    int index_first, index_second;
    // Copy elements from list1 to the beginning of result
    for (index_first = 0; index_first < first_array_size; index_first++) {
        combined_array[index_first] = first_array[index_first];
    }
    // Append elements from list2 to the end of result
    for (index_second = 0; index_second < second_array_size; index_second++) {
        combined_array[first_array_size + index_second] = second_array[index_second];
    }
}