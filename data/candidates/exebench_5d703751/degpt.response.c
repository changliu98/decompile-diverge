// Restricts the value pointed to by pvar to be within the range [r1, r2].
// If *pvar is less than r1, it is set to r1.
// If *pvar is greater than r2, it is set to r2.
void iw_restrict_to_range(int min_val, int max_val, int *value_ptr)
{
  // Clamp lower bound: if value is below minimum, set to minimum
  if (*value_ptr < min_val) {
    *value_ptr = min_val;
  }
  // Clamp upper bound: if value is above maximum, set to maximum
  else if (max_val < *value_ptr) {
    *value_ptr = max_val;
  }
}