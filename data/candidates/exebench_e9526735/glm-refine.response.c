Optimized and annotated for reverse engineering
void __cdecl removeslave(int *slave, int n)
{
  // The original loop iterates from 9 down to 0, indicating a fixed-size array of 10 elements.
  // We use a pointer to track the current position, which is more idiomatic in decompilation.
  int *p_slave = &slave[9];

  // Iterate backward through the 10-element array
  for (int i = 0; i < 10; ++i)
  {
    // If we have cleared the requested number of slaves, exit early
    if (n == 0)
      break;

    // Check if the current slave slot is active (non-zero)
    if (*p_slave)
    {
      *p_slave = 0; // Deactivate/clear the slave
      --n;          // Decrement the remaining count to remove
    }

    --p_slave; // Move to the previous element in the array
  }
}