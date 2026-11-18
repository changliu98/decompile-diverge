// Increments the value pointed to by the pointer x by 1
void increment(int *valuePtr)
{
  // Add 1 to the current value of x and store it back in the memory location pointed to by x
  *valuePtr = *valuePtr + 1;
}