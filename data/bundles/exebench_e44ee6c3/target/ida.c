int __cdecl compare(int *min, int *mid, int *max)
{
  int temp; // [rsp+0h] [rbp-1Ch]
  int tempa; // [rsp+0h] [rbp-1Ch]
  int tempb; // [rsp+0h] [rbp-1Ch]

  if ( *min > *mid )
  {
    temp = *min;
    *min = *mid;
    *mid = temp;
  }
  if ( *min > *max )
  {
    tempa = *min;
    *min = *max;
    *max = tempa;
  }
  if ( *mid > *max )
  {
    tempb = *mid;
    *mid = *max;
    *max = tempb;
  }
  return 0;
}