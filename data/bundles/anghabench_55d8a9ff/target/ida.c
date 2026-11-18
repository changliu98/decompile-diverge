int __cdecl byte_col_big5(int byte)
{
  if ( byte >= 64 && byte < 127 )
    return byte - 64;
  if ( byte < 161 || byte >= 255 )
    return -1;
  return byte - 98;
}