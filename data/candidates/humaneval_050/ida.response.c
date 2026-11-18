void __cdecl func0(char *s, int encode)
{
  int v2; // eax
  size_t i; // [rsp+10h] [rbp-20h]
  size_t len; // [rsp+18h] [rbp-18h]
  int shift; // [rsp+20h] [rbp-10h]

  v2 = 21;
  if ( encode )
    v2 = 5;
  shift = v2;
  len = strlen(s);
  for ( i = 0LL; i < len; ++i )
    s[i] = (shift + s[i] - 97) % 26 + 97;
}