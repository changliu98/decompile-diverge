int __cdecl memcasecmp(const void *vs1, const void *vs2, size_t n)
{
  const unsigned char *s1 = (const unsigned char *)vs1;
  const unsigned char *s2 = (const unsigned char *)vs2;

  for (size_t i = 0; i < n; ++i)
  {
    int diff = toupper(s1[i]) - toupper(s2[i]);
    if (diff)
      return diff;
  }
  return 0;
}