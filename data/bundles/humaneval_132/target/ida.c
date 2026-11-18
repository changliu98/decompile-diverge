int __cdecl func0(const char *str)
{
  int i; // [rsp+14h] [rbp-1Ch]
  int maxcount; // [rsp+18h] [rbp-18h]
  int count; // [rsp+1Ch] [rbp-14h]

  count = 0;
  maxcount = 0;
  for ( i = 0; i < strlen(str); ++i )
  {
    if ( str[i] == 91 )
      ++count;
    if ( str[i] == 93 )
      --count;
    if ( count < 0 )
      count = 0;
    if ( count > maxcount )
      maxcount = count;
    if ( count <= maxcount - 2 )
      return 1;
  }
  return 0;
}