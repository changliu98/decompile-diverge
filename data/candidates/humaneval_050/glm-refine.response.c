void __cdecl func0(char *s, int encode)
{
  int shift = encode ? 5 : 21;
  size_t len = strlen(s);

  for (size_t i = 0; i < len; ++i)
  {
    // Apply a Caesar cipher shift to lowercase letters ('a' to 'z')
    s[i] = ((s[i] - 'a' + shift) % 26) + 'a';
  }
}