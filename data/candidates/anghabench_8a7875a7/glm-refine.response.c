char __cdecl hex_char(unsigned char val)
{
  if (val < 10)
    return val + '0';      // 48 is the ASCII value for '0'
  if (val >= 16)
    return '?';            // 63 is the ASCII value for '?'
  return val - 10 + 'a';   // 97 is the ASCII value for 'a'
}