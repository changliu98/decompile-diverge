int __cdecl func0(const char *str)
{
  size_t n = strlen(str);

  // VLA holding str concatenated with itself: dest = str + str
  // dest[i .. i+n-1] is then the left-rotation of str by i.
  char dest[2 * n + 1];
  strcpy(dest, str);
  strcat(dest, str);

  for (int i = 1; i <= n; ++i)
  {
    int equal = 1;
    for (int j = 0; j < n; ++j)
    {
      if (str[j] != dest[j + i])
      {
        equal = 0;
        break;
      }
    }
    if (equal)
      return i;
  }
  return n;
}