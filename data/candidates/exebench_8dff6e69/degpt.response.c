// Performs the operation: dy[i] = dy[i] + dx[i] for all elements in the vectors.
// This is a BLAS Level 1 routine equivalent to DAXPY with alpha=1.
//
// Parameters:
//   n   - Number of elements in the vectors.
//   dx  - Pointer to the first element of the source vector.
//   dy  - Pointer to the first element of the destination vector (updated in place).
void dxpy1(int num_elements, double *source_vector, double *destination_vector)
{
    for (int index = 0; index < num_elements; index++) {
        destination_vector[index] += source_vector[index];
    }
}