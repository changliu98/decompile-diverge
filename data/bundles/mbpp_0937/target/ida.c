char __cdecl func0(const char *str1)
{
  int i; // [rsp+0h] [rbp-420h]
  int len; // [rsp+4h] [rbp-41Ch]
  char max_char; // [rsp+Bh] [rbp-415h]
  int max_freq; // [rsp+Ch] [rbp-414h]
  int frequency[256]; // [rsp+10h] [rbp-410h] BYREF
  const char *str1a; // [rsp+418h] [rbp-8h]

  str1a = str1;
  memset(frequency, 0, sizeof(frequency));
  max_freq = 0;
  max_char = 0;
  len = strlen(str1a);
  for ( i = 0; i < len; ++i )
  {
    if ( ++frequency[(unsigned __int8)str1a[i]] > max_freq )
    {
      max_freq = frequency[(unsigned __int8)str1a[i]];
      max_char = str1a[i];
    }
  }
  return max_char;
}