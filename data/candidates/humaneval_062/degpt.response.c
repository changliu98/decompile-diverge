void func0(float *input_array, int array_length, float *output_array)
{
    // Iterate through the input array starting from the second element
    for (int index = 1; index < array_length; index++) {
        // Multiply the current index by the current element and store in the output array
        output_array[index - 1] = (float)index * input_array[index];
    }
}