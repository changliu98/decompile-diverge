// Adds two 16-element float arrays element-wise and stores the result in 'result'
void mlMatrixAddTo(float *lhs, float *rhs, float *output)
{
    uint index;
    // Iterate through all 16 elements (0x10 = 16)
    for (index = 0; index < 0x10; index = index + 1) {
        // Add corresponding elements from arrays 'a' and 'b', store in 'result'
        output[index] = lhs[index] + rhs[index];
    }
}