void func0(int *input_array, int array_length, int *output_values)
{
    int total_sum = 0;          // Initialize sum to zero
    int total_product = 1;      // Initialize product to one
    for (int index = 0; index < array_length; index++) {
        total_sum += input_array[index];    // Add current element to sum
        total_product *= input_array[index]; // Multiply current element to product
    }
    *output_values = total_sum;          // Store sum in the first element of result
    output_values[1] = total_product;    // Store product in the second element of result
}