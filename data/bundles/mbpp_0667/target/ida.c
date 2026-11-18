int __cdecl func0(const char *string, const char *vowels)
{
  const char *v; // [rsp+0h] [rbp-28h]
  int count; // [rsp+14h] [rbp-14h]

  count = 0;
  while ( *string )
  {
    for ( v = vowels; *v; ++v )
    {
      if ( *string == *v )
      {
        ++count;
        break;
      }
    }
    ++string;
  }
  return count;
}