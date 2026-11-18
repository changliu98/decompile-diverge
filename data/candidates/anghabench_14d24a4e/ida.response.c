unsigned int __cdecl sgl_len(unsigned int n)
{
  return (((_BYTE)n - 1) & 1) + ((3 * (n - 1)) >> 1) + 2;
}