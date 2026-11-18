void __cdecl func0(const int *lst, int size, int *result)
{
  int i; // [rsp+0h] [rbp-24h]
  int minpos; // [rsp+4h] [rbp-20h]
  int maxneg; // [rsp+8h] [rbp-1Ch]

  maxneg = 0;
  minpos = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( lst[i] < 0 && (!maxneg || lst[i] > maxneg) )
      maxneg = lst[i];
    if ( lst[i] > 0 && (!minpos || lst[i] < minpos) )
      minpos = lst[i];
  }
  *result = maxneg;
  result[1] = minpos;
}