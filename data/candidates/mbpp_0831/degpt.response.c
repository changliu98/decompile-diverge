int func0(int *numbers, int size)
{
    int duplicate_pair_count = 0; // Initialize counter for duplicate pairs
    for (int index_first = 0; index_first < size; index_first++) { // Iterate through each element
        for (int index_second = index_first + 1; index_second < size; index_second++) { // Compare with subsequent elements
            if (numbers[index_first] == numbers[index_second]) { // Check if elements are equal
                duplicate_pair_count++; // Increment count for each duplicate pair found
            }
        }
    }
    return duplicate_pair_count; // Return total number of duplicate pairs
}