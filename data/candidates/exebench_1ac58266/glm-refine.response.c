void __cdecl max1D_double(double *input, int len, MaxResult *retVals)
{
    // Initialize the result with default values
    retVals->index = -1.0;
    retVals->value = -INFINITY;

    // Iterate through the input array to find the maximum value
    for (int i = 0; i < len; ++i)
    {
        if (input[i] > retVals->value)
        {
            retVals->value = input[i];
            retVals->index = (double)i;
        }
    }
}