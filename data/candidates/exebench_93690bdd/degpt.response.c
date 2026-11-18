// Limits the value pointed to by x to be within the range [lower, upper].
// If *x is less than lower, it is set to lower.
// If *x is greater than upper, it is set to upper.
// Otherwise, *x remains unchanged.
void limit2_i32(int *value_ptr, int min_val, int max_val)
{
    if (*value_ptr < min_val) {
        *value_ptr = min_val;
    } else if (*value_ptr > max_val) {
        *value_ptr = max_val;
    }
}