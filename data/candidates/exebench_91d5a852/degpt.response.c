// Converts an integer value into its four constituent bytes in little-endian order.
// Parameters:
//   val   - The integer value to convert.
//   bytes - A pointer to a character array where the bytes will be stored.
void to_bytes(int value,char *buffer)
{
  // Store the least significant byte (bits 0-7)
  *buffer = (char)value;
  // Store the second byte (bits 8-15)
  buffer[1] = (char)((uint)value >> 8);
  // Store the third byte (bits 16-23)
  buffer[2] = (char)((uint)value >> 0x10);
  // Store the most significant byte (bits 24-31)
  buffer[3] = (char)((uint)value >> 0x18);
}