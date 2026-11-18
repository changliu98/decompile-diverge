int affs_intl_toupper(int ch)
{
  if (ch >= 'a' && ch <= 'z')
    return ch;
  if (ch >= 0xe0 && ch <= 0xfe && ch != 0xf7)
    return ch - 0x20;
  return ch;
}