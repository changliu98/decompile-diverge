void BinaryFiles__swap_bytes32(uint *value)

{
  uint result;
  uint *value_local;
  
  *value = *value * 0x1000000 + (*value & 0xff00) * 0x100 + ((*value & 0xff0000) >> 8) +
           (*value >> 0x18);
  return;
}