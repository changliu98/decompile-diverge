int ilog2(unsigned_long v)

{
  int l;
  unsigned_long v_local;
  
  for (l = 0; (ulong)(1L << ((byte)l & 0x3f)) < v; l = l + 1) {
  }
  return l;
}