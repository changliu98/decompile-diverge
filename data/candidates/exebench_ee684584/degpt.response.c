int clipmaxdouble(double *values, double max_value, long size)
{
    // Iterate through the array of doubles
    for (long i = 0; i < size; i++) {
        // If the current element exceeds the maximum value, clip it to xmax
        if (max_value < values[i]) {
            values[i] = max_value;
        }
    }
    // Return success status
    return 0;
}