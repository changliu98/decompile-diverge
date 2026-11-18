unsigned int __cdecl frag_num(unsigned int i)
{
  return (i & 0xFFFFFFFC) + 3 - (i & 3);
}