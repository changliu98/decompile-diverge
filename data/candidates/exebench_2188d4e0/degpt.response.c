void f(int *value_a, int *value_b)
{
  // If the value pointed to by b is less than the value pointed to by a
  if (*value_b < *value_a) {
    // Halve the value pointed to by a
    *value_a = *value_a / 2;
    // Double the value pointed to by b
    *value_b = *value_b << 1;
  }
  else {
    // Double the value pointed to by a
    *value_a = *value_a << 1;
    // Halve the value pointed to by b
    *value_b = *value_b / 2;
  }
}