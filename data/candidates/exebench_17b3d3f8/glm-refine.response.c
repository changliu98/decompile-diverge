void __cdecl gsm_hex_from_byte(char *hex, int val)
{
  // Extract the high 4 bits (upper nibble) and convert to a hex character
  hex[0] = gsm_hex_from_byte_hexdigits[(val >> 4) & 0xF];
  
  // Extract the low 4 bits (lower nibble) and convert to a hex character
  hex[1] = gsm_hex_from_byte_hexdigits[val & 0xF];
}