int __cdecl func0(const char *string, char c)
{
  int i; // [rsp+0h] [rbp-20h]
  int length; // [rsp+4h] [rbp-1Ch]
  int flag; // [rsp+8h] [rbp-18h]

  flag = -1;
  length = strlen(string);
  for ( i = 0; i < length; ++i )
  {
    if ( string[i] == c )
      flag = i;
  }
  if ( flag == -1 )
    return -1;
  else
    return flag + 1;
}