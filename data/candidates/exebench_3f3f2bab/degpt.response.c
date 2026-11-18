/**
 * Checks if the lower bound array is strictly less than the upper bound array.
 *
 * @param lb Pointer to the lower bound array.
 * @param ub Pointer to the upper bound array.
 * @param m  Number of elements in the arrays.
 * @return 1 if all elements in lb are strictly less than corresponding elements in ub, 0 otherwise.
 */
int sboxCHECK(float *lower_bounds, float *upper_bounds, int size)
{
    // Check if both pointers are valid
    if (lower_bounds && upper_bounds) {
        // Iterate through each element of the arrays
        for (int index = 0; index < size; index++) {
            // If any upper bound is less than or equal to the corresponding lower bound, return 0
            if (upper_bounds[index] <= lower_bounds[index]) {
                return 0;
            }
        }
    }
    // Return 1 if all lower bounds are strictly less than upper bounds
    return 1;
}