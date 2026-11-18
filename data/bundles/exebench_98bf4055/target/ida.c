void __cdecl reverseIntRange(int *pStart, int *pEnd, int size)
{
  int temp; // [rsp+0h] [rbp-18h]

  temp = *pStart;
  *pStart = size - *pEnd;
  *pEnd = size - temp;
}