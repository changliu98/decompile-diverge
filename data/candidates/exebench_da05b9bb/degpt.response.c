// Reference implementation for dividing two floating-point numbers
// Parameters:
//   arg1:   The dividend (numerator)
//   arg2:   The divisor (denominator)
//   result: Pointer to store the result of arg1 / arg2
void ref_div_float(float dividend, float divisor, float *output)
{
    // Perform floating-point division and store the result
    *output = dividend / divisor;
}