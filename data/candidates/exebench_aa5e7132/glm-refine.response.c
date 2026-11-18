void __cdecl GetWord(char *out, const char *in, int max)
{
  int count = 0;

  // Skip leading whitespace (ASCII control characters and space)
  while (*in > 0 && *in <= 32)
    ++in;

  // Copy non-whitespace characters up to max - 1
  while (count < max - 1 && *in > 32)
  {
    *out++ = *in++;
    ++count;
  }

  // Null-terminate the output string
  *out = 0;
}