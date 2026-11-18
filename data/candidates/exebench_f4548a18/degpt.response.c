// Increments the value pointed to by 'a' by 1
// Returns -5 regardless of input
int increase_1(int *ptr)
{
  // Increment the value at the memory address pointed to by 'a'
  *ptr = *ptr + 1;
  // Return constant value -5
  return -5;
}