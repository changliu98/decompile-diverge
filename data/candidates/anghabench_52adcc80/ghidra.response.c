unsigned_short BigUnsignedShort(unsigned_short l)

{
  byte b2;
  byte b1;
  unsigned_short l_local;
  
  return l * 0x100 + (l >> 8);
}