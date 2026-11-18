unsigned int __cdecl fons__decutf8(unsigned int *state, unsigned int *codep, unsigned int byte)
{
  unsigned int codepoint;
  unsigned int type;

  // Look up the character type from the 256-byte lookup table
  type = fons__decutf8_utf8d[byte];

  // If we are in the initial ACCEPT state, this byte is the start of a new sequence.
  // We extract the payload bits by masking the byte based on the sequence type.
  // Otherwise, we are in the middle of a sequence, so we shift the existing 
  // codepoint and append the 6 continuation bits (0x3F).
  if (*state == FONS_UTF8_ACCEPT)
    codepoint = byte & (255 >> type);
  else
    codepoint = (*codep << 6) | (byte & 0x3F);

  *codep = codepoint;

  // Look up the next state from the 256-byte state transition table.
  // The new state is determined by the current byte type and the current state.
  *state = fons__decutf8_utf8d[256 + type + *state];

  return *state;
}