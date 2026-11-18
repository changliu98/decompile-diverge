int __cdecl get_char_utf8(unsigned int *out_char, const char *str)
{
  unsigned int c0 = (unsigned char)str[0];

  // 1-byte sequence (ASCII)
  if ((c0 & 0x80) == 0)
  {
    *out_char = c0;
    return c0 != 0;
  }

  // Invalid leading byte (10xxxxxx)
  if ((c0 & 0x40) == 0)
    goto fail;

  unsigned int c1 = (unsigned char)str[1];
  if ((c1 & 0xC0) != 0x80)
    goto fail;

  // 2-byte sequence
  if ((c0 & 0x20) == 0)
  {
    if ((c0 & 0x1E) == 0)
      goto fail;
    *out_char = (c0 << 6) + (c1 & 0x3F);
    return 2;
  }

  unsigned int c2 = (unsigned char)str[2];
  if ((c2 & 0xC0) != 0x80)
    goto fail;

  // 3-byte sequence
  if ((c0 & 0x10) == 0)
  {
    if ((c0 & 0x0F) == 0 && (c1 & 0x20) == 0)
      goto fail;
    *out_char = (c0 << 12) + (c1 << 6) + (c2 & 0x3F);
    return 3;
  }

  unsigned int c3 = (unsigned char)str[3];
  if ((c3 & 0xC0) != 0x80)
    goto fail;

  // 4-byte sequence
  if ((c0 & 0x08) == 0)
  {
    if ((c0 & 0x07) == 0 && (c1 & 0x30) == 0)
      goto fail;
    *out_char = (c0 << 18) + (c1 << 12) + (c2 << 6) + (c3 & 0x3F);
    return 4;
  }

  unsigned int c4 = (unsigned char)str[4];
  if ((c4 & 0xC0) != 0x80)
    goto fail;

  // 5-byte sequence
  if ((c0 & 0x04) == 0)
  {
    if ((c0 & 0x03) == 0 && (c1 & 0x38) == 0)
      goto fail;
    *out_char = (c0 << 24) + (c1 << 18) + (c2 << 12) + (c3 << 6) + (c4 & 0x3F);
    return 5;
  }

  unsigned int c5 = (unsigned char)str[5];
  if ((c5 & 0xC0) != 0x80)
    goto fail;

  // 6-byte sequence
  if ((c0 & 0x02) != 0)
    goto fail;

  if ((c0 & 0x01) == 0 && (c1 & 0x3C) == 0)
    goto fail;

  *out_char = ((c0 & 0x01) << 30) + (c1 << 24) + (c2 << 18) + (c3 << 12) + (c4 << 6) + (c5 & 0x3F);
  return 6;

fail:
  *out_char = -1;
  return -1;
}