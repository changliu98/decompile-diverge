// Stores a 32-bit integer 'd' into memory at pointer 'p' in little-endian byte order.
void dwordstore(char *buffer,int value)
{
  // Store the least significant byte (bits 0-7)
  *buffer = (char)value;
  // Store the second least significant byte (bits 8-15)
  buffer[1] = (char)((uint)value >> 8);
  // Store the third least significant byte (bits 16-23)
  buffer[2] = (char)((uint)value >> 0x10);
  // Store the most significant byte (bits 24-31)
  buffer[3] = (char)((uint)value >> 0x18);
}