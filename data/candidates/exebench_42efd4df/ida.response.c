int __cdecl getMax(int a, int b, int c, int *max)
{
  int tmpMax; // [rsp+0h] [rbp-20h]
  int choice; // [rsp+4h] [rbp-1Ch]

  choice = 1;
  tmpMax = a;
  if ( a < b )
  {
    tmpMax = b;
    choice = 2;
  }
  if ( tmpMax < c )
  {
    tmpMax = c;
    choice = 3;
  }
  *max = tmpMax;
  return choice;
}