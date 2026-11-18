void func3(int threshold, int *counter_ptr)
{
  // If i is less than 1, decrement the value pointed to by j
  if (threshold < 1) {
    *counter_ptr = *counter_ptr - 1;
  }
  // Otherwise, increment the value pointed to by j
  else {
    *counter_ptr = *counter_ptr + 1;
  }
}