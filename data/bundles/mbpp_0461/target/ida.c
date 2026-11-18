int __cdecl func0(const char *str)
{
  int upper_ctr; // [rsp+Ch] [rbp-14h]
  int v3; // [rsp+1Ch] [rbp-4h]

  upper_ctr = 0;
  if ( strlen(str) )
  {
    if ( *str >= 65 )
      return *str <= 90;
    return upper_ctr;
  }
  return v3;
}