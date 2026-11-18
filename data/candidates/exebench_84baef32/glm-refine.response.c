// Global lookup table (assumed to be defined elsewhere in the binary)
extern const char itoa_hex_hexatab[16];

// Converts a 32-bit unsigned integer to an 8-character lowercase/uppercase 
// hexadecimal string (without a null terminator).
void __cdecl itoa_hex(unsigned int val, char *buf)
{
  char *p = &buf[8]; // Start at the end of the 8-character buffer

  do
  {
    // Pre-decrement pointer, then assign the hex character for the lowest 4 bits
    *--p = itoa_hex_hexatab[val & 0xF];
    
    // Shift right by 4 bits to process the next nibble
    val >>= 4;
  } 
  while (p != buf); // Loop exactly 8 times until we reach the beginning of the buffer
}