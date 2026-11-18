char __cdecl hex_char(unsigned __int8 val)
{
  if ( val < 0xAu )
    return val + 48;
  if ( val >= 0x10u )
    return 63;
  return val - 10 + 97;
}