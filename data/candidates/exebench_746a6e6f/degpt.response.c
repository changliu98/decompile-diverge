void arrayadd(int *source_array, int *destination_array)
{
    // Iterate through the arrays for 50 elements (0x32 in hexadecimal)
    for (int index = 0; index < 0x32; index++) {
        // Add 5 to each element of array 'a' and store the result in array 'b'
        destination_array[index] = source_array[index] + 5;
    }
}