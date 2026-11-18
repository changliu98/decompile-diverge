void __cdecl swap(int *x, int *y)
{
  int temp; // [rsp+0h] [rbp-14h]

  if ( x )
  {
    if ( y )
    {
      temp = *x;
      *x = *y;
      *y = temp;
    }
  }
}