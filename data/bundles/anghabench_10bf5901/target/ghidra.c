int affs_intl_toupper(int ch)

{
  int local_10;
  int ch_local;
  
  if (((0x60 < ch) && (ch < 0x7b)) || ((local_10 = ch, 0xdf < ch && ((ch < 0xff && (ch != 0xf7))))))
  {
    local_10 = ch + -0x20;
  }
  return local_10;
}