void gsm_hex_from_byte(char *hex, int val)
{
  hex[0] = gsm_hex_from_byte_hexdigits[(val >> 4) & 0xf];
  hex[1] = gsm_hex_from_byte_hexdigits[(val & 0xf)];
}