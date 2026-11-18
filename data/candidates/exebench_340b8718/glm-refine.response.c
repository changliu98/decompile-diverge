char *__cdecl strtoupper(char *s)
{
  for (int i = 0; i < 8; ++i)
  {
    if (s[i] >= 'a' && s[i] <= 'z')
      s[i] -= 32; // 32 is the ASCII difference between lowercase and uppercase
    // If it's not a lowercase letter, it remains unchanged
  }
  return s;
}