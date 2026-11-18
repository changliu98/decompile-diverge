// Limits the value pointed to by x to be within the range [lower, upper].
// If *x is less than lower, it is set to lower.
// If *x is greater than upper, it is set to upper.
void limit2_u16(unsigned_short *value, unsigned_short min_val, unsigned_short max_val)
{
  if (*value < min_val) {
    *value = min_val;
  } else if (*value > max_val) {
    *value = max_val;
  }
}