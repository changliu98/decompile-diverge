// Calculates the sum of the first two elements in the float array pointed to by 'floats'.
// Note: This function assumes the array has at least two elements.
float SumAFloatArray(float *values)
{
    // Returns the sum of the first element (*floats) and the second element (floats[1]).
    return *values + values[1];
}