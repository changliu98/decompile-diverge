void swap(int *ptr_a, int *ptr_b)
{
  // Check if both pointers are valid (non-NULL) before dereferencing
  if (ptr_a && ptr_b) {
    // Store the value pointed to by x in a temporary variable
    int temp_value = *ptr_a;
    // Assign the value pointed to by y to the location pointed to by x
    *ptr_a = *ptr_b;
    // Assign the original value of *x (stored in temp) to the location pointed to by y
    *ptr_b = temp_value;
  }
}