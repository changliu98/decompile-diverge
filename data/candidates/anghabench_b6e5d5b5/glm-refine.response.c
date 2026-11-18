void __cdecl packInt32(uint8_t *buffer, uint32_t value)
{
  buffer[0] = (uint8_t)value;
  *(uint16_t *)(buffer + 1) = (uint16_t)(value >> 8);
  buffer[3] = (uint8_t)(value >> 24);
}