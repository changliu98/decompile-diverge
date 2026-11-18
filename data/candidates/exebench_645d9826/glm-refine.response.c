char *__cdecl byte2bin(char in, char *out)
{
  for (int n = 0; n < 8; ++n)
  {
    // Check if the n-th most significant bit is set
    if ((in & (1 << (7 - n))) != 0)
      out[n] = '1';
    else
      out[n] = '0';
  }
  
  // Null-terminate the string
  out[8] = '\0';
  
  return out;
}