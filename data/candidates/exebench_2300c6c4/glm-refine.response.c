char *__cdecl strtoupper(char *s)
{
  for (int i = 0; i < 8; ++i)
  {
    if (s[i] >= 'a' && s[i] <= 'z')
      s[i] = toupper(s[i]); // or simply: s[i] -= 32;
    else
      s[i] = s[i]; // This is a no-op left over from the decompiler's v2 assignment
  }
  return s;
}