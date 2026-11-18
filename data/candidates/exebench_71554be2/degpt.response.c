// Subtracts arg2 from arg1 and stores the result in the memory location pointed to by result.
void ref_sub_double(double minuend, double subtrahend, double *difference_ptr)
{
    // Calculate the difference between arg1 and arg2
    *difference_ptr = minuend - subtrahend;
}