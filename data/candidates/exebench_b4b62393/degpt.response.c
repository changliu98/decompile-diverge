void intercambiar(int *ptr_a, int *ptr_b)
{
  // Check if the two pointers are not pointing to the same memory location
  if (ptr_a != ptr_b) {
    // Store the value pointed to by pos1 in a temporary variable
    int temp_value = *ptr_a;
    // Assign the value pointed to by pos2 to the location pointed to by pos1
    *ptr_a = *ptr_b;
    // Assign the stored value (original value of *pos1) to the location pointed to by pos2
    *ptr_b = temp_value;
  }
}