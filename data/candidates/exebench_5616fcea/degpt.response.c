// Increments the integer value pointed to by val by 1
void do_something(int *target_value)
{
  // Add 1 to the current value at the memory location pointed to by val
  *target_value = *target_value + 1;
}