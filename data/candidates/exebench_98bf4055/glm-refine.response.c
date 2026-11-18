void __cdecl reverseIntRange(int *pStart, int *pEnd, int size)
{
  int original_start = *pStart;
  
  // Mirror the end value relative to size and assign it to start
  *pStart = size - *pEnd;
  
  // Mirror the original start value relative to size and assign it to end
  *pEnd = size - original_start;
}