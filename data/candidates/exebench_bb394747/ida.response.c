int __cdecl get_hashmask(int *size)
{
  int tsize; // [rsp+0h] [rbp-Ch]

  for ( tsize = 1; tsize < *size; tsize *= 2 )
    ;
  *size = tsize;
  return tsize - 1;
}