int __cdecl byte_row_johab_hangul(int byte)
{
  if ( byte < 132 || byte >= 212 )
    return -1;
  else
    return byte - 132;
}