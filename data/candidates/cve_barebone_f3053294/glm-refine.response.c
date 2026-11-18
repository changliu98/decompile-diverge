define UNICODE_REPLACEMENT_CHAR 0xFFFD

char *__cdecl utf_16le_to_utf_8_truncated(const wchar_t *utf_16, char *utf_8, size_t utf_8_len)
{
  char *utf_8_ptr = utf_8;
  size_t remaining_len = utf_8_len;

  if (!remaining_len)
    return utf_8;

  while (1)
  {
    wchar_t c = *utf_16++;
    if (!c)
      break;

    uint32_t uc;

    // Check for High Surrogates
    if (c >= HIGH_SURROGATE_START && c <= HIGH_SURROGATE_END)
    {
      wchar_t c2 = *utf_16;
      if (c2)
      {
        ++utf_16;
        if (c2 >= LOW_SURROGATE_START && c2 <= LOW_SURROGATE_END)
          uc = (((c - HIGH_SURROGATE_START) << 10) | (c2 - LOW_SURROGATE_START)) + 0x10000;
        else
          uc = UNICODE_REPLACEMENT_CHAR;
      }
      else
      {
        uc = UNICODE_REPLACEMENT_CHAR;
      }
    }
    // Check for unpaired Low Surrogates
    else if (c >= LOW_SURROGATE_START && c <= LOW_SURROGATE_END)
    {
      uc = UNICODE_REPLACEMENT_CHAR;
    }
    else
    {
      uc = c;
    }

    // Encode to UTF-8
    if (uc < 0x80)
    {
      if (remaining_len < 2)
        break;
      *utf_8_ptr++ = (char)uc;
      --remaining_len;
    }
    else if (uc < 0x800)
    {
      if (remaining_len < 3)
        break;
      *utf_8_ptr++ = (char)(((uc >> 6) & 0x1F) | 0xC0);
      *utf_8_ptr++ = (char)((uc & 0x3F) | 0x80);
      remaining_len -= 2;
    }
    else if (uc < 0x10000)
    {
      if (remaining_len < 4)
        break;
      *utf_8_ptr++ = (char)(((uc >> 12) & 0x0F) | 0xE0);
      *utf_8_ptr++ = (char)(((uc >> 6) & 0x3F) | 0x80);
      *utf_8_ptr++ = (char)((uc & 0x3F) | 0x80);
      remaining_len -= 3;
    }
    else // uc >= 0x10000
    {
      if (remaining_len < 5)
        break;
      *utf_8_ptr++ = (char)(((uc >> 18) & 0x07) | 0xF0);
      *utf_8_ptr++ = (char)(((uc >> 12) & 0x3F) | 0x80);
      *utf_8_ptr++ = (char)(((uc >> 6) & 0x3F) | 0x80);
      *utf_8_ptr++ = (char)((uc & 0x3F) | 0x80);
      remaining_len -= 4;
    }
  }

  *utf_8_ptr = 0;
  return utf_8_ptr;
}