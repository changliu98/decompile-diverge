int __cdecl func0(const char *num)
{
  int i; // [rsp+8h] [rbp-18h]
  int out; // [rsp+Ch] [rbp-14h]

  out = 0;
  for ( i = 0; i < strlen(num); ++i )
  {
    if ( strchr("2357BD", num[i]) )
      ++out;
  }
  return out;
}