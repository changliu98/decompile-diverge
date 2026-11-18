void __cdecl packInt32(uint8_t *buffer, uint32_t value)
{
  *buffer = value;
  *(_WORD *)(buffer + 1) = value >> 8;
  buffer[3] = HIBYTE(value);
}