int __cdecl getMax(int a, int b, int c, int *max)
{
  int currentMax = a;
  int maxIndex = 1;

  if (a < b) 
  {
    currentMax = b;
    maxIndex = 2;
  }
  
  if (currentMax < c) 
  {
    currentMax = c;
    maxIndex = 3;
  }
  
  *max = currentMax;
  return maxIndex;
}