void packInt32(uint8_t *buffer,uint32_t value)

{
  uint32_t value_local;
  uint8_t *buffer_local;
  
  *buffer = (uint8_t)value;
  buffer[1] = (uint8_t)(value >> 8);
  buffer[2] = (uint8_t)(value >> 0x10);
  buffer[3] = (uint8_t)(value >> 0x18);
  return;
}