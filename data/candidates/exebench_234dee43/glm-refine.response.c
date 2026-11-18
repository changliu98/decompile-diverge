const char *__cdecl utf8_to_ucs4(const char *ptr, uint32_t *result)
{
  const char *next;
  int i;
  int shift;
  int octet_count;
  unsigned char lead_byte;
  uint32_t code_point;

  next = ptr + 1;
  lead_byte = *(unsigned char *)ptr;

  // 1-byte sequence: 0xxxxxxx
  if ((lead_byte & 0x80) == 0)
  {
    if (result)
      *result = lead_byte;
    return next;
  }

  // Determine sequence length and extract leading payload bits
  if ((lead_byte & 0xE0) == 0xC0)       // 2-byte sequence: 110xxxxx
  {
    octet_count = 2;
    code_point = lead_byte & 0x1F;
  }
  else if ((lead_byte & 0xF0) == 0xE0)  // 3-byte sequence: 1110xxxx
  {
    octet_count = 3;
    code_point = lead_byte & 0x0F;
  }
  else if ((lead_byte & 0xF8) == 0xF0)  // 4-byte sequence: 11110xxx
  {
    octet_count = 4;
    code_point = lead_byte & 0x07;
  }
  else if ((lead_byte & 0xFC) == 0xF8)  // 5-byte sequence: 111110xx (Historical/Non-standard)
  {
    octet_count = 5;
    code_point = lead_byte & 0x03;
  }
  else if ((lead_byte & 0xFE) == 0xFC)  // 6-byte sequence: 1111110x (Historical/Non-standard)
  {
    octet_count = 6;
    code_point = lead_byte & 0x01;
  }
  else
  {
    // Invalid leading byte
    return 0LL;
  }

  // Process continuation bytes: 10xxxxxx
  shift = 6 * (octet_count - 1);
  code_point <<= shift;

  for (i = 1; i < octet_count; ++i)
  {
    shift -= 6;
    unsigned char cont_byte = *next++;
    
    if ((cont_byte & 0xC0) != 0x80)
      return 0LL;
      
    code_point |= (cont_byte & 0x3F) << shift;
  }

  if (result)
    *result = code_point;
    
  return next;
}