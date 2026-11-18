void daxpy(uint count, double scalar, double *vector_x, double *vector_y)
{
    // Perform the operation only if da is non-zero or NaN
    if (scalar != 0.0 || NAN(scalar)) {
        // Iterate backwards through the arrays
        for (uint index = count; index > 0; index--) {
            // Update dy[i-1] with da * dx[i-1] + dy[i-1]
            vector_y[index - 1] = scalar * vector_x[index - 1] + vector_y[index - 1];
        }
    }
}