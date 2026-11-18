int __cdecl affs_intl_toupper(int ch_0)
{
  if ( (ch_0 < 97 || ch_0 > 122) && (ch_0 < 224 || ch_0 > 254 || ch_0 == 247) )
    return ch_0;
  else
    return ch_0 - 32;
}