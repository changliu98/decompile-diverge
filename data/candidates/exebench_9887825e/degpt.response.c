// Checks for multiplication overflow when calculating a * b.
// If res is NULL, the result is stored in a local variable.
// Returns 1 if overflow occurs, 0 otherwise.
int safe_calloc_check_mul(size_t lhs, size_t rhs, size_t *output)
{
    size_t local_result;
    size_t *result_ptr = output;
    // If res pointer is NULL, use a local variable to store the result
    if (output == NULL) {
        result_ptr = &local_result;
    }
    // Perform the multiplication and store the result
    *result_ptr = lhs * rhs;
    // Check for overflow: if the product is less than either operand, overflow occurred
    return (lhs * rhs < lhs || lhs * rhs < rhs) ? 1 : 0;
}