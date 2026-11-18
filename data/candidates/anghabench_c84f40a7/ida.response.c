int __cdecl byte_row_gbk1(int byte)
{
  if ( byte < 129 || byte >= 255 )
    return -1;
  else
    return byte - 129;
}