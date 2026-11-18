void swap(float *lower_bound, float *upper_bound)
{
  // Check if the value pointed to by max is less than the value pointed to by min
  if (*upper_bound < *lower_bound) {
    // Store the value of *max in a temporary variable
    float swap_buffer = *upper_bound;
    // Assign the value of *min to *max
    *upper_bound = *lower_bound;
    // Assign the original value of *max (stored in temp) to *min
    *lower_bound = swap_buffer;
  }
}