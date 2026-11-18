size_t __cdecl base_len(const char *name)
{
  bool v2; // [rsp+7h] [rbp-19h]
  size_t len; // [rsp+10h] [rbp-10h]

  for ( len = strlen(name); ; --len )
  {
    v2 = 0;
    if ( len > 1 )
      v2 = name[len - 1] == 47;
    if ( !v2 )
      break;
  }
  return len;
}