void __cdecl gsm_hex_from_byte(char *hex, int val)
{
  *hex = gsm_hex_from_byte_hexdigits[(val >> 4) & 0xF];
  hex[1] = gsm_hex_from_byte_hexdigits[val & 0xF];
}