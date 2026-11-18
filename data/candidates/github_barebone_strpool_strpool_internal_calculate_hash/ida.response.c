unsigned int __cdecl strpool_internal_calculate_hash(const char *string, int length, int ignore_case)
{
  char v5; // [rsp+4h] [rbp-28h]
  int i_0; // [rsp+Ch] [rbp-20h]
  char c; // [rsp+13h] [rbp-19h]
  int i; // [rsp+14h] [rbp-18h]
  int hash; // [rsp+18h] [rbp-14h]

  hash = 5381;
  if ( ignore_case )
  {
    for ( i = 0; i < length; ++i )
    {
      c = string[i];
      if ( c > 122 || c < 97 )
        v5 = string[i];
      else
        v5 = c - 32;
      hash = v5 ^ (33 * hash);
    }
  }
  else
  {
    for ( i_0 = 0; i_0 < length; ++i_0 )
      hash = string[i_0] ^ (33 * hash);
  }
  if ( hash )
    return hash;
  else
    return 1;
}