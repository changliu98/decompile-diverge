// Subtracts vector b from vector a in-place
// a: destination vector (modified)
// b: source vector (unchanged)
void mlPointSub(float *destination, float *source)
{
    // Iterate over the 3 components of the vectors
    for (uint index = 0; index < 3; index++) {
        // Subtract corresponding component of b from a
        destination[index] -= source[index];
    }
}