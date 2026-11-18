// Function to add two floating-point numbers and store the result in the pointer r
// Parameters:
//   n1: First floating-point number
//   n2: Second floating-point number
//   r: Pointer to store the sum of n1 and n2
// Returns:
//   Always returns 0.0
float somar(float first_number, float second_number, float *result_pointer)
{
    // Calculate the sum of n1 and n2 and store it in the memory location pointed to by r
    *result_pointer = first_number + second_number;
    // Return 0.0 (indicating success or no error)
    return 0.0;
}