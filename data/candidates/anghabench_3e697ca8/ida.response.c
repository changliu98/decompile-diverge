unsigned int __cdecl swizzle(unsigned int in, unsigned int limit)
{
  unsigned int out; // [rsp+0h] [rbp-Ch]

  out = 0;
  while ( limit )
  {
    out = in & 1 | (2 * out);
    in >>= 1;
    limit >>= 1;
  }
  return out;
}