uLong multmodp(uLong a,uLong b)

{
  ulong local_30;
  uLong p;
  uLong m;
  uLong b_local;
  uLong a_local;
  
  m = 0x80000000;
  p = 0;
  b_local = b;
  while (((a & m) == 0 || (p = b_local ^ p, (a & m - 1) != 0))) {
    m = m >> 1;
    if ((b_local & 1) == 0) {
      local_30 = b_local >> 1;
    }
    else {
      local_30 = b_local >> 1 ^ 0xedb88320;
    }
    b_local = local_30;
  }
  return p;
}