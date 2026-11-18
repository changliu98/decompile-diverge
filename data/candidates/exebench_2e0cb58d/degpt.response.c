void r3add(double *result, double *operand)
{
    // Add the first element of v to the first element of u
    *result = *operand + *result;
    // Add the second element of v to the second element of u
    result[1] = operand[1] + result[1];
    // Add the third element of v to the third element of u
    result[2] = operand[2] + result[2];
}