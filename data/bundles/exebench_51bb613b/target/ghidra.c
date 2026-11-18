int rand_r(uint *nextp)

{
  uint *nextp_local;
  
  *nextp = *nextp * 0x41c64e6d + 0x3039;
  return *nextp >> 0x10 & 0x7fff;
}