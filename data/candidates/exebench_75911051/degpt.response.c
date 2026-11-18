// Function to perform integer division and calculate the remainder
// Parameters:
//   a - The dividend
//   b - The divisor
//   remainder - Pointer to store the remainder of the division
// Returns:
//   The quotient of a divided by b
int divide(int dividend, int divisor, int *remainder_ptr)
{
    // Calculate the remainder of a divided by b and store it in the memory location pointed to by remainder
    *remainder_ptr = dividend % divisor;
    
    // Return the quotient of a divided by b
    return dividend / divisor;
}