void _kahan_summation_step(double input_value, double *running_sum, double *compensation_error, double *adjusted_value, double *intermediate_sum)
{
    // Adjust the new value by subtracting the accumulated error
    *adjusted_value = input_value - *compensation_error;
    // Add the adjusted value to the current sum
    *intermediate_sum = *running_sum + *adjusted_value;
    // Calculate the new error term (rounding error from the addition)
    *compensation_error = (*intermediate_sum - *running_sum) - *adjusted_value;
    // Update the sum with the result of the addition
    *running_sum = *intermediate_sum;
}