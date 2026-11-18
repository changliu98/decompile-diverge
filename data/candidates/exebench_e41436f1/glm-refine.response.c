void __cdecl htond(double *x)
{
  // Cast the double pointer to a 32-bit integer pointer for word manipulation
  DWORD *p = (DWORD *)x;
  
  // Swap the 32-bit halves and convert each to big-endian (network byte order)
  DWORD high_word = p[0];
  p[0] = htonl(p[1]);
  p[1] = htonl(high_word);
}