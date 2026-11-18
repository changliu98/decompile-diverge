void _itoa_hex(uint number, char *buffer)
{
  // Convert the unsigned integer 'val' to an 8-character hexadecimal string
  for (uint index = 0; index < 8; index++) {
    // Extract the least significant 4 bits of 'val'
    // Use them as an index to get the corresponding hex character
    // Store the character in the buffer from right to left (least significant nibble first)
    buffer[7 - index] = "0123456789ABCD"[number & 0xf];
    // Shift 'val' right by 4 bits to process the next nibble
    number >>= 4;
  }
}