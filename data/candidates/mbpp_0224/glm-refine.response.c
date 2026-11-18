int __cdecl func0(int n)
{
  int count = 0;
  
  // Counts the number of set bits (1s) in the integer 'n'
  // using Brian Kernighan's algorithm.
  while (n)
  {
    n &= n - 1;
    count++;
  }
  
  return count;
}