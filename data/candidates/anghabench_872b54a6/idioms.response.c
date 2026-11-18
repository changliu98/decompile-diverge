int byte_row_johab_hangul(int key)
{
  if (key >= 132 && key < 212)
    return key - 132;
  return -1;
}