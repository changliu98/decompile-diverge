uint ether_hash(uchar *ea)

{
  int i;
  uint hash;
  uchar *ea_local;
  
  hash = 0;
  for (i = 0; i < 6; i = i + 1) {
    hash = (uint)ea[i] + hash * 0x1003f;
  }
  return hash;
}