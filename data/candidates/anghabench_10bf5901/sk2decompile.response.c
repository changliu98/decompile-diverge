static int affs_intl_toupper(int c) {
  if ((c >= 'a' && c <= 'z') || (c >= 0xE0 && c <= 0xFE && c != 0xF7))
    return c - 0x20;
  return c;
}