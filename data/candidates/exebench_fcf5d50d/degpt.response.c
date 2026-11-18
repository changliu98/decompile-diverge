// Performs element-wise multiplication of arrays X and Y, then adds the result to array Z.
// Z[i] = X[i] * Y[i] + Z[i] for all i from 0 to N-1.
void mult_add_into_cpu(int size, float *input_array_a, float *input_array_b, float *output_array)
{
    int index;
    // Iterate through each element of the arrays
    for (index = 0; index < size; index++) {
        // Multiply corresponding elements from X and Y, then add to existing value in Z
        output_array[index] = input_array_a[index] * input_array_b[index] + output_array[index];
    }
}