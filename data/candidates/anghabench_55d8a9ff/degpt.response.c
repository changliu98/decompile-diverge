int byte_col_big5(int input_byte)
{
  // Check if byte is in the ASCII range (0x00-0x3F) or invalid range (0x80-0xFF)
  if ((input_byte < 0x40) || (0x7e < input_byte)) {
    // For non-ASCII bytes, check if it's in the valid Big5 range (0xA1-0xFE)
    if ((input_byte < 0xa1) || (0xfe < input_byte)) {
      // Return -1 if byte is outside the valid Big5 range
      return -1;
    }
    else {
      // Convert valid Big5 byte to column index by subtracting 0x62
      return input_byte - 0x62;
    }
  }
  else {
    // For ASCII bytes (0x40-0x7E), convert to column index by subtracting 0x40
    return input_byte - 0x40;
  }
}