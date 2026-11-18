int __cdecl func0(const char *string, char c)
{
  int i; // [rsp+Ch] [rbp-14h]
  int count; // [rsp+10h] [rbp-10h]

  count = 0;
  for ( i = 0; i < strlen(string); ++i )
  {
    if ( string[i] == c )
      ++count;
  }
  return count;
}