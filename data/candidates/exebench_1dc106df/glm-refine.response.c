char *__cdecl i2hs(unsigned int n, char *ds_0)
{
  const char *hex_chars = "0123456789ABCDEF";
  char ts[32];
  char *tsp = ts + 1; // Start 1 byte ahead to safely use negative indexing
  char *dsp = ds_0;

  // Convert the number to hex characters in reverse order
  while (n)
  {
    *tsp++ = hex_chars[n & 0xF];
    n >>= 4;
  }

  // If n was originally 0, the loop is skipped. Add a single '0'.
  if (tsp == ts + 1)
  {
    *tsp++ = '0';
  }

  // Reverse the string and copy it to the destination buffer
  do
  {
    *dsp++ = *--tsp;
  }
  while (*tsp); // Stops after copying the null-terminator from ts[0]

  return ds_0;
}