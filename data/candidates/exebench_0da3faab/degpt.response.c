void mac_real(float *input_data, float *kernel, float *output_data)
{
    // Perform MAC operation on the first element: y[0] = x[0] * h[0] + y[0]
    *output_data = *input_data * *kernel + *output_data;
    
    // Perform MAC operation on the second element: y[1] = x[1] * h[0] + y[1]
    output_data[1] = input_data[1] * *kernel + output_data[1];
}