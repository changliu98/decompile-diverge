uint fons__decutf8(uint *state,uint *codep,uint byte)

{
  byte bVar1;
  uint local_24;
  uint type;
  uint byte_local;
  uint *codep_local;
  uint *state_local;
  
  bVar1 = ""[byte];
  if (*state == FONS_UTF8_ACCEPT) {
    local_24 = 0xff >> (bVar1 & 0x1f) & byte;
  }
  else {
    local_24 = byte & 0x3f | *codep << 6;
  }
  *codep = local_24;
  *state = (uint)""[*state + 0x100 + (uint)bVar1];
  return *state;
}