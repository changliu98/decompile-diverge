/*
 * Updates the value pointer based on variable index and maximum variable count.
 *
 * Parameters:
 *   valptr   - Pointer to store the resulting value.
 *   varptr   - Pointer to the current variable index.
 *   maxvar   - Pointer to the maximum variable index encountered so far.
 *   mpptr    - Pointer to the new value to potentially store.
 *   linkvals - Array storing linked values for variables.
 *
 * Returns:
 *   1 if a new maximum variable index was set or initial value was assigned.
 *   0 otherwise.
 */
int modpars_to_struct(float *result_value, int *current_var_index, int *max_var_index, float *new_value, float *variable_values)
{
    // Case 1: First variable encountered; assign the new value directly.
    if (*current_var_index == 1) {
        *result_value = *new_value;
        return 1;
    }
    // Case 2: Current variable index exceeds the maximum seen so far;
    // update maximum, store the value in linkvals, and assign to valptr.
    else if (*max_var_index < *current_var_index) {
        *result_value = *new_value;
        *max_var_index = *current_var_index;
        variable_values[(long)*current_var_index - 2] = *new_value;
        return 1;
    }
    // Case 3: Variable index is less than 2 (invalid or already handled);
    // do not update value.
    else if (*current_var_index < 2) {
        return 0;
    }
    // Case 4: Variable index is within known range; retrieve previously stored value.
    else {
        *result_value = variable_values[(long)*current_var_index - 2];
        return 0;
    }
}