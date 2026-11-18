void __cdecl hex_to_word(char *two_chars, char hex)
{
  if ( two_chars )
  {
    // Extract the high and low nibbles
    two_chars[0] = (hex >> 4) & 0xF;
    two_chars[1] = hex & 0xF;

    // Convert the 4-bit integer values to their ASCII hex representations
    for ( int i = 0; i < 2; ++i )
    {
      char nibble = two_chars[i];
      
      // If 0-9, add '0' (48). If 10-15, add 'A' - 10 (55).
      two_chars[i] = (nibble <= 9) ? nibble + '0' : nibble + 'A' - 10;
    }
  }
}