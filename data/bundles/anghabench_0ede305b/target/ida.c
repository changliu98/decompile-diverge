unsigned int __cdecl fons__decutf8(unsigned int *state, unsigned int *codep, unsigned int byte)
{
  unsigned int v4; // [rsp+0h] [rbp-1Ch]
  unsigned int type; // [rsp+4h] [rbp-18h]

  type = fons__decutf8_utf8d[byte];
  if ( *state == FONS_UTF8_ACCEPT )
    v4 = byte & (255 >> type);
  else
    v4 = (*codep << 6) | byte & 0x3F;
  *codep = v4;
  *state = fons__decutf8_utf8d[type + 256 + *state];
  return *state;
}