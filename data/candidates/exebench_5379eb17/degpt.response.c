void max_ptr(int *first_value, int *second_value)
{
  // If the value pointed to by q is less than the value pointed to by p
  if (*second_value < *first_value) {
    // Swap the values pointed to by p and q using XOR swap algorithm
    *first_value = *first_value ^ *second_value;
    *second_value = *first_value ^ *second_value;
    *first_value = *first_value ^ *second_value;
  }
}