int __cdecl lockoff(int *block)
{
  *block = 0; // Unlock the block
  return 0;   // Return success
}