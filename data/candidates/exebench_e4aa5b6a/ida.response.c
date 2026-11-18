int __cdecl util_read_dec(char *str, int *result)
{
  long tmp2; // [rsp+0h] [rbp-30h]
  int i; // [rsp+Ch] [rbp-24h]
  int tmp; // [rsp+10h] [rbp-20h]
  int neg; // [rsp+14h] [rbp-1Ch]
  char *stra; // [rsp+20h] [rbp-10h]

  stra = str;
  neg = 0;
  i = 0;
  *result = 0;
  if ( *str == 45 )
  {
    neg = 1;
    stra = str + 1;
    i = 1;
  }
  for ( tmp2 = 0LL; *stra; *result = tmp2 )
  {
    tmp = *stra - 48;
    if ( (unsigned int)tmp >= 0xA )
      break;
    tmp2 = 10 * tmp2 + tmp;
    if ( tmp2 > 0x7FFFFFFF )
      break;
    ++stra;
    ++i;
  }
  if ( !neg )
    return i;
  if ( i != 1 )
  {
    *result = -*result;
    return i;
  }
  return 0;
}