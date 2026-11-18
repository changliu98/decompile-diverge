void __cdecl func0(const char *s, char *out)
{
  int i; // [rsp+4h] [rbp-14h]

  for ( i = 0; s[i]; ++i )
    out[i] = (s[i] - 97 + 4) % 26 + 97;
  out[i] = 0;
}