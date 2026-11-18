utf8proc_ssize_t __cdecl utf8proc_iterate(const utf8proc_uint8_t *str, utf8proc_ssize_t strlen, utf8proc_int32_t *dst)
{
  utf8proc_ssize_t max_len;
  const utf8proc_uint8_t *end;
  const utf8proc_uint8_t *next_str;
  unsigned int uc;
  int decoded_char;

  *dst = -1;
  
  if (!strlen)
    return 0;
    
  // If strlen is negative, assume a maximum of 4 bytes (standard UTF-8 upper bound)
  max_len = (strlen >= 0) ? strlen : 4;
  end = str + max_len;
  next_str = str + 1;
  uc = *str;

  // ASCII character (0x00 - 0x7F)
  if (uc < 0x80)
  {
    *dst = uc;
    return 1;
  }

  // Check for valid leading byte range (0xC2 - 0xF4)
  // (uc - 194 <= 0x32) is equivalent to (uc >= 0xC2 && uc <= 0xF4)
  if (uc - 194 > 0x32)
    return -3;

  // 4-byte sequence (0xF0 - 0xF4)
  if (uc >= 0xF0)
  {
    if (str + 3 < end && 
        (*next_str & 0xC0) == 0x80 && 
        (str[2] & 0xC0) == 0x80 && 
        (str[3] & 0xC0) == 0x80)
    {
      // Overlong / out-of-range checks for code points > U+10FFFF
      if (uc == 0xF0 && *next_str < 0x90)
        return -3;
      if (uc == 0xF4 && *next_str > 0x8F)
        return -3;

      *dst = (uc & 0x07) << 18 | 
             (str[1] & 0x3F) << 12 | 
             (str[2] & 0x3F) << 6  | 
             (str[3] & 0x3F);
      return 4;
    }
    return -3;
  }
  // 3-byte sequence (0xE0 - 0xEF)
  else if (uc >= 0xE0)
  {
    if (str + 2 < end && 
        (*next_str & 0xC0) == 0x80 && 
        (str[2] & 0xC0) == 0x80)
    {
      // Check for surrogates (U+D800 - U+DFFF)
      if (uc == 0xED && *next_str > 0x9F)
        return -3;

      decoded_char = (uc & 0x0F) << 12 | 
                     (str[1] & 0x3F) << 6 | 
                     (str[2] & 0x3F);
      
      // Check for overlong sequences (code points < 0x800)
      if (decoded_char < 0x800)
        return -3;

      *dst = decoded_char;
      return 3;
    }
    return -3;
  }
  // 2-byte sequence (0xC2 - 0xDF)
  else
  {
    if (next_str < end && (*next_str & 0xC0) == 0x80)
    {
      *dst = (uc & 0x1F) << 6 | 
             (*next_str & 0x3F);
      return 2;
    }
    return -3;
  }
}