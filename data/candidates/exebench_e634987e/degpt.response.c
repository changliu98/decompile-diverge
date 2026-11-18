// Increments the value pointed to by the given pointer by 1.
void increment(int *value_ptr)
{
  // Add 1 to the current value stored at the memory address referenced by cell.
  *value_ptr = *value_ptr + 1;
}