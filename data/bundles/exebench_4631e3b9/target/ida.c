int __cdecl c_decrypt(char *text)
{
  while ( *text )
    *text++ -= 13;
  return 0;
}